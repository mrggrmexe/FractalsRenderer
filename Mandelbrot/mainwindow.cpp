#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QVariantAnimation>
#include <QTimer>
#include <QMouseEvent>
#include <QMetaType>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QCoreApplication>
#include <algorithm>

using ld = long double;

//================ FractalWorker ==================

static inline void zPow(int64_t power, ld& zr, ld& zi)
{
    if (power == 2) {
        const ld zr2 = zr*zr - zi*zi;
        const ld zi2 = 2.0*zr*zi;
        zr = zr2; zi = zi2;
        return;
    }
    const ld r0 = zr, i0 = zi;
    for (int64_t k = 1; k < power; ++k) {
        const ld nzr = zr*r0 - zi*i0;
        const ld nzi = zr*i0 + zi*r0;
        zr = nzr; zi = nzi;
    }
}

void FractalWorker::render(RenderParams p)
{
    m_cancel.store(false, std::memory_order_relaxed);

    const qreal dpr = qMax<qreal>(1.0, p.devicePixelRatio);
    const int64_t W = qMax(1, int64_t(p.width  * dpr));
    const int64_t H = qMax(1, int64_t(p.height * dpr));

    QImage img(W, H, QImage::Format_RGB32);
    img.setDevicePixelRatio(dpr);

    int64_t colored = 0;
    int64_t black   = 0;
    int64_t lastReported = -1;

    for (int64_t y = 0; y < H; ++y) {
        if (m_cancel.load(std::memory_order_relaxed)) return;

        const ld yLogical = ld(y) / dpr;
        QRgb* line = reinterpret_cast<QRgb*>(img.scanLine(y));

        for (int64_t x = 0; x < W; ++x) {
            if (m_cancel.load(std::memory_order_relaxed)) return;

            const ld xLogical = ld(x) / dpr;
            const ld cr = (p.starti + xLogical / p.scale) / 240.0;
            const ld ci = (p.startj - yLogical / p.scale) / 240.0;

            ld zr = 0.0, zi = 0.0;
            bool escaped = false;
            int64_t itVal = 0;

            for (int64_t it = 0; it < p.maxIterations; ++it) {
                zPow(p.power, zr, zi);
                zr += cr; zi += ci;

                if ((zr*zr + zi*zi) >= 4.0) {
                    escaped = true;
                    itVal = it;
                    break;
                }
            }

            if (escaped) {
                const int64_t r = ( (itVal * 20) % 100 );
                const int64_t g = ( itVal % 200 );
                const int64_t b = ( (itVal * 20) % 255 + 25 );
                line[x] = qRgb(r, g, b);
                ++colored;
            } else {
                line[x] = qRgb(0, 0, 0);
                ++black;
            }
        }

        const int64_t percent = int64_t((y + 1) * 100.0 / H + 0.5);
        if (percent != lastReported && (percent == 100 || percent % 2 == 0)) {
            lastReported = percent;
            emit progress(percent);
        }
    }

    if (!m_cancel.load(std::memory_order_relaxed)) {
        emit imageReady(img, black, colored);
    }
}

//================ MainWindow ==================

static inline bool isDigitStr(const QString& s) {
    if (s.isEmpty()) return false;
    for (QChar c : s) if (!c.isDigit()) return false;
    return true;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaType<RenderParams>("RenderParams");
    ui->setupUi(this);
    on_application_open();
    scene = new QGraphicsScene(this);
    ui->myView->setScene(scene);
    pixItem = scene->addPixmap(QPixmap());
    scene->setSceneRect(0, 0, viewWidth, viewHeight);
    ui->myView->setInteractive(false);
    m_chooseOverlay = ui->choose;
    m_chooseOverlay->setParent(ui->myView->viewport());
    m_chooseOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    m_chooseOverlay->setStyleSheet(
        "background: rgba(207,105,255,0.20);"
        "border: 1px dashed rgba(207,105,255,0.9);"
        );
    m_chooseOverlay->hide();
    ui->myView->viewport()->installEventFilter(this);
    workerThread = new QThread(this);
    worker = new FractalWorker();
    worker->moveToThread(workerThread);
    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::destroyed, workerThread, &QThread::quit);
    connect(worker, &FractalWorker::progress, this, &MainWindow::onRenderProgress, Qt::QueuedConnection);
    connect(worker, &FractalWorker::imageReady, this, &MainWindow::onRenderImage, Qt::QueuedConnection);
    workerThread->start();
}

MainWindow::~MainWindow()
{
    if (worker) worker->cancel();
    if (workerThread) {
        workerThread->quit();
        workerThread->wait();
    }
    delete ui;
}

void MainWindow::on_application_open()
{
    ImageRender logo(ui->centralwidget);
    logo.setPath(":/pictures/van.png");
    logo.setSize(40, 40);
    logo.setPos(7, 7);
    logo.render();

    auto *effectGlow = new QGraphicsDropShadowEffect(this);
    effectGlow->setBlurRadius(25);
    effectGlow->setXOffset(1);
    effectGlow->setYOffset(-1);
    effectGlow->setColor(QColor(173, 191, 255));
    ui->glow->setGraphicsEffect(effectGlow);

    ui->label->setText("-");
    ui->label_2->setText("-");
    ui->label_3->setText("-");
    ui->label_4->setText("-");
    ui->label_5->setText("");

    resetViewState();
}

void MainWindow::resetViewState()
{
    m_scale  = 1.0;
    m_starti = -280.0;
    m_startj =  240.0;

    const QSize sz = ui->myView->viewport()->size();
    viewWidth  = sz.width()  > 0 ? sz.width()  : 560;
    viewHeight = sz.height() > 0 ? sz.height() : 420;

    ui->glow->setGeometry(40, 550, 0, 3);
}

bool MainWindow::isPositiveInteger(const QString &s)
{
    return isDigitStr(s);
}

void MainWindow::setGlowProgress(int64_t percent)
{
    percent = std::clamp((int)percent, 0, 100);
    const int64_t w = int64_t(kGlowMaxWidth * (percent / 100.0));
    QRect r = ui->glow->geometry();
    r.setWidth(w);
    ui->glow->setGeometry(r);
    ui->label_5->setText(QString::number(percent) + "%");
    if (percent == 100) {
        QTimer::singleShot(300, this, [this]{
            ui->label_5->setText("");
            ui->glow->setGeometry(40, 550, 0, 3);
        });
    }
}

// ——— Indicators ———
void MainWindow::blinkWidgets(const QList<QWidget*>& widgets, qreal fadeTo, int64_t totalMs)
{
    for (QWidget* w : widgets) {
        if (!w) continue;
        auto *eff = qobject_cast<QGraphicsOpacityEffect*>(w->graphicsEffect());
        if (!eff) {
            eff = new QGraphicsOpacityEffect(w);
            eff->setOpacity(1.0);
            w->setGraphicsEffect(eff);
        }

        auto *down = new QPropertyAnimation(eff, "opacity", w);
        down->setDuration(totalMs/2);
        down->setStartValue(1.0);
        down->setEndValue(fadeTo);

        auto *up = new QPropertyAnimation(eff, "opacity", w);
        up->setDuration(totalMs/2);
        up->setStartValue(fadeTo);
        up->setEndValue(1.0);

        auto *seq = new QSequentialAnimationGroup(w);
        seq->addAnimation(down);
        seq->addAnimation(up);
        seq->setLoopCount(1);
        seq->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void MainWindow::updateInfoLabels(int64_t black, int64_t colored)
{
    ui->label->setText(QString::number(int64_t(m_scale)));
    ui->label_2->setText(QString::number(int64_t(m_starti)) + " " +
                         QString::number(int64_t(m_startj)));
    ui->label_3->setText(QString::number(black));
    ui->label_4->setText(QString::number(colored));

    blinkWidgets({ ui->label, ui->label_2, ui->label_3, ui->label_4 }, 0.35, 240);
}

void MainWindow::startRender(int64_t power)
{
    if (!worker) return;

    worker->cancel();

    const QSize sz = ui->myView->viewport()->size();
    viewWidth  = sz.width()  > 0 ? sz.width()  : 560;
    viewHeight = sz.height() > 0 ? sz.height() : 420;

    RenderParams p;
    p.power = power;
    p.starti = m_starti;
    p.startj = m_startj;
    p.scale  = m_scale;
    p.width  = viewWidth;
    p.height = viewHeight;
    p.maxIterations = 1000;
    p.devicePixelRatio = ui->myView->devicePixelRatioF();

    m_lastProgress = -1;
    setGlowProgress(0);

    QMetaObject::invokeMethod(worker, "render", Qt::QueuedConnection, Q_ARG(RenderParams, p));
}

// -------- Build --------

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setGeometry(20, 150, 261, 41);

    resetViewState();

    const QString text = ui->lineEdit->text().trimmed();
    int64_t power = 2;
    if (isPositiveInteger(text)) {
        bool ok = false;
        const int64_t v = text.toInt(&ok);
        if (ok && v >= 2 && v <= 20) power = int64_t(v);
    }

    startRender(power);
}

void MainWindow::on_pushButton_pressed()
{
    const QString text = ui->lineEdit->text().trimmed();
    const bool ok = isPositiveInteger(text);
    const QString oldStyle = ui->pushButton->styleSheet();

    if (ok) ui->pushButton->setStyleSheet("background-color: #43ff89; color: black;");
    for (int64_t i = 0; i < 5; ++i) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
        ui->pushButton->setGeometry(20 + i/2, 150 + i/2, 261 - i, 41 - i);
    }
    if (ok) {
        QTimer::singleShot(20, this, [this, oldStyle]{ ui->pushButton->setStyleSheet(oldStyle); });
    }
}

void MainWindow::on_pushButton_released()
{
    ui->pushButton->setGeometry(20, 150, 261, 41);
}

// -------- worker -> UI --------

void MainWindow::onRenderProgress(int64_t percent)
{
    if (percent == m_lastProgress) return;
    m_lastProgress = percent;
    setGlowProgress(percent);
}

void MainWindow::onRenderImage(const QImage &img, int64_t black, int64_t colored)
{
    QPixmap px = QPixmap::fromImage(img);
    pixItem->setPixmap(px);
    scene->setSceneRect(QRectF(QPointF(0,0),
                               QSizeF(px.width()/px.devicePixelRatioF(), px.height()/px.devicePixelRatioF())));

    updateInfoLabels(black, colored);

    if (m_chooseOverlay) m_chooseOverlay->hide();
}

// -------- Zoom myView --------

bool MainWindow::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == ui->myView->viewport()) {
        switch (ev->type()) {
        case QEvent::MouseButtonPress: {
            auto *me = static_cast<QMouseEvent*>(ev);
            if (me->button() == Qt::LeftButton) {
                m_selecting = true;
                m_selStart = me->pos();
                m_chooseOverlay->setGeometry(QRect(m_selStart, QSize(1,1)));
                m_chooseOverlay->show();
                return true;
            }
            break;
        }
        case QEvent::MouseMove: {
            if (!m_selecting) break;
            auto *me = static_cast<QMouseEvent*>(ev);
            const QPoint cur = me->pos();

            const ld aspect = viewWidth / ld(viewHeight);
            int64_t x1 = qMin(m_selStart.x(), cur.x());
            int64_t y1 = qMin(m_selStart.y(), cur.y());
            int64_t x2 = qMax(m_selStart.x(), cur.x());
            int64_t y2 = qMax(m_selStart.y(), cur.y());
            int64_t h = y2 - y1;

            if (h <= 0) h = 1;
            int64_t w = int64_t(h * aspect);
            if ((x1 + w) > viewWidth) w = viewWidth - x1;

            m_chooseOverlay->setGeometry(QRect(QPoint(x1, y1), QSize(w, h)));
            return true;
        }
        case QEvent::MouseButtonRelease: {
            auto *me = static_cast<QMouseEvent*>(ev);
            if (m_selecting && me->button() == Qt::LeftButton) {
                m_selecting = false;

                QRect rr = m_chooseOverlay->geometry();
                m_chooseOverlay->hide();

                if (rr.width() > 5 && rr.height() > 5) {
                    const ld x = rr.x();
                    const ld y = rr.y();
                    const ld b = rr.height();

                    m_starti = m_starti + x / m_scale;
                    m_startj = m_startj - y / m_scale;
                    m_scale  = m_scale * (ld(viewHeight) / b);

                    QString text = ui->lineEdit->text().trimmed();
                    int64_t power = 2;
                    if (isPositiveInteger(text)) {
                        bool ok = false;
                        const int64_t v = text.toInt(&ok);
                        if (ok && v >= 2 && v <= 20) power = int64_t(v);
                    }
                    startRender(power);
                }
                return true;
            }
            break;
        }
        default:
            break;
        }
    }
    return QMainWindow::eventFilter(obj, ev);
}
