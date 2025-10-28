#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QThread>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPointer>
#include <atomic>

#include "imagerender.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// ---------------- RenderParams ----------------
struct RenderParams {
    int64_t power = 2;
    long double starti = -280.0;
    long double startj =  240.0;
    long double scale  = 1.0;
    int64_t width  = 560;
    int64_t height = 420;
    int64_t maxIterations = 2000;
    qreal devicePixelRatio = 1.0;
};
Q_DECLARE_METATYPE(RenderParams)

// ---------------- FractalWorker ----------------
class FractalWorker : public QObject {
    Q_OBJECT
public:
    explicit FractalWorker(QObject* parent = nullptr) : QObject(parent) {}
public slots:
    void render(RenderParams p);
    void cancel() { m_cancel.store(true, std::memory_order_relaxed); }
signals:
    void progress(int64_t percent);
    void imageReady(const QImage& img, int64_t black, int64_t colored);
private:
    std::atomic_bool m_cancel{false};
};

// ---------------- MainWindow ----------------
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_application_open();
    void on_pushButton_clicked();
    void on_pushButton_pressed();
    void on_pushButton_released();

    void onRenderProgress(int64_t percent);
    void onRenderImage(const QImage& img, int64_t black, int64_t colored);

protected:
    bool eventFilter(QObject* obj, QEvent* ev) override;

private:
    void startRender(int64_t power);
    static bool isPositiveInteger(const QString& s);
    void resetViewState();
    void updateInfoLabels(int64_t black, int64_t colored);
    void setGlowProgress(int64_t percent);
    void blinkWidgets(const QList<QWidget*>& widgets, qreal fadeTo = 0.35, int64_t totalMs = 240);

private:
    Ui::MainWindow *ui = nullptr;

    QGraphicsScene* scene = nullptr;
    QGraphicsPixmapItem* pixItem = nullptr;

    QThread* workerThread = nullptr;
    FractalWorker* worker = nullptr;

    double m_scale  = 1.0;
    double m_starti = -280.0;
    double m_startj =  240.0;

    bool m_selecting = false;
    QPoint m_selStart;
    QWidget* m_chooseOverlay = nullptr;

    int m_lastProgress = -1;

    int viewWidth  = 560;
    int viewHeight = 420;

    const int kGlowMaxWidth = 911;
};

#endif // MAINWINDOW_H
