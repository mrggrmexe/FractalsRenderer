#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include "QGraphicsDropShadowEffect"
#include "QGraphicsOpacityEffect"
#include "QColor"
#include "QLabel"
#include "QLineEdit"
#include "QTime"
#include "QDir"
#include "QSize"
#include "QFile"
#include <vector>
#include <iostream>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QTimer>

#include "complex.h"
#include "myclassscene.h"

#pragma GCC optimize("O1,O2,O3,Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,sse4,sse4.1,sse4.2,avx,tune=native")


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_application_open();
}

MainWindow::~MainWindow()
{
    delete ui;
}


// ДИНАМИЧЕСКАЯ БАЗА ДАННЫХ /////////////////////////////////

bool isActivated_lineEdit = 0;
short glow = 0;

short bx = 0, by = 0;

bool ticked = 0;

int64_t activPosition = -1;

QGraphicsOpacityEffect *op;
QGraphicsOpacityEffect *op2;
QGraphicsDropShadowEffect *effect;
QGraphicsDropShadowEffect *effectglow;

myClassScene *picture;
QGraphicsItemGroup *group;

std::vector<std::pair<QLabel*, QLineEdit*>> valueChoose;

double centeri = 280, centerj = 240;
double scale = 1;
double movei = 0;
double movej = 0;

double starti = -280;
double startj = 240;

bool inproccess = 0;

/////////////////////////////////////////////////////////////


void delay1(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

double my_pow(double a, short b) {

    if (b == 0) return 1;

    double tmp = a;

    for (short i = 0; i < b; ++i) {

        a *= tmp;
    }

    return a;

}


void MainWindow::on_application_open() {

    ImageRender logo(ui->centralwidget);
    logo.setPath(":/pictures/van.png");
    logo.setSize(40, 40);
    logo.setPos(7, 7);
    logo.render();

    effectglow = new QGraphicsDropShadowEffect;
    effectglow->setColor(QColor(0, 0, 0));

    op = new QGraphicsOpacityEffect;
    op->setOpacity(0.0);

    op2 = new QGraphicsOpacityEffect;
    op2->setOpacity(0.3);

    ui->kostil->setGraphicsEffect(op);
    ui->choose->setGraphicsEffect(op2);

    effectglow->setBlurRadius(25);
    effectglow->setXOffset(1);
    effectglow->setYOffset(-1);
    effectglow->setColor(QColor(173, 191, 255));
    ui->glow->setGraphicsEffect(effectglow);

    ui->myView->setInteractive(false);

    ui->label_5->setText("");

}



void MainWindow::buildPic(short s) {

    inproccess = 1;

    if (picture == nullptr) {

        picture = new myClassScene;
        group = new QGraphicsItemGroup;
        picture->addItem(group);
        ui->myView->setScene(picture);

        int width = 560;
        int height = 420;

        picture->setSceneRect(0,0,width,height);

    } else {

        foreach(QGraphicsItem *item, picture->items(group->boundingRect())) {

            if(item->group() == group) {

                delete item;
            }
        }
        delete picture;
        picture = new myClassScene;
        group = new QGraphicsItemGroup;
        picture->addItem(group);
        ui->myView->setScene(picture);
        picture->setSceneRect(0,0,560,420);

    }

    ui->glow->setGeometry(40, 550, 0, 3);
    double wi = 0;
    short perm = 0;

    //QColor arr[560][480];
    int colored = 0;
    int black = 0;

    ui->myView->hide();

    ui->choose->setGeometry(-800, -800, 0, 0);

    for (short i = 0; i < 560; ++i) {
        for (short j = 0; j < 480; ++j) {

            double m; double n;

            ++perm;
            if (perm == 2900) {
                ui->glow->setGeometry(40, 550, ui->glow->geometry().width() + 10, 3);
                perm = 0;

                int needme = ui->glow->geometry().width() / 911.0 * 100;
                ui->label_5->setText(QString::fromStdString(std::to_string(needme)) + "%");
                delay1(1);
            }

            m = (starti + i / scale) / (240.0);
            n = (startj - j / scale) / (240.0);


            Complex c(m, n);


            bool flag = 1;
            short need = 0;
            Complex z(0, 0);

            if (scale > 2) {
                for (short r = 0; r < 1500 && flag; ++r) {

                    for (short pow = 0; pow < s - 1; ++pow) {
                        z.powPermutation();
                    }

                    z.addOther(c);


                    if (z.ro() >= 2) {
                        flag = 0;

                    }
                    need = r;

                }
            } else {
                for (short r = 0; r < 10000 && flag; ++r) {

                    for (short pow = 0; pow < s - 1; ++pow) {
                        z.powPermutation();
                    }

                    z.addOther(c);


                    if (z.ro() >= 2) {
                        flag = 0;

                    }
                    need = r;

                }
            }

            if (!flag) {
                group->addToGroup(picture->addRect(i, j, 1, 0, QColor(((need * 20) % 100) % 255, need % 255, ((need * 20) % 255 + 25))));
                ++colored;
            } else {
                group->addToGroup(picture->addRect(i, j, 1, 0, QColor(0, 0, 0)));
                ++black;
            }

        }
    }
    ui->myView->show();

    ui->glow->setGeometry(40, 550, 0, 3);

    ui->label->setText(QString::fromStdString(std::to_string(int(scale))));
    ui->label_2->setText(QString::fromStdString(std::to_string(int(starti))) + " " +
                         QString::fromStdString(std::to_string(int(startj))));
    ui->label_3->setText(QString::fromStdString(std::to_string(black)));
    ui->label_4->setText(QString::fromStdString(std::to_string(colored)));

    ui->label_5->setText("");

    inproccess = 0;

}



void MainWindow::play_animation() {


}


void MainWindow::on_pushButton_clicked()
{

    ui->pushButton->setGeometry(20, 150, 261, 41);

    centeri = 280;
    centerj = 240;
    scale = 1;
    movej = 0;
    movei = 0;
    starti = -280;
    startj = 240;

    delay1(100);
    buildPic(std::stoi(ui->lineEdit->text().toStdString()));

    if (!glow) {
        play_animation();
    }


}

void MainWindow::on_pushButton_pressed()
{
    for (short i = 0; i < 5; ++i) {
        delay1(10);
        ui->pushButton->setGeometry(20 + i / 2, 150 + i / 2, 261 - i, 41 - i);
    }
}


void MainWindow::on_pushButton_released()
{
    ui->pushButton->setGeometry(20, 150, 261, 41);
}


void MainWindow::mouseMoveEvent(QMouseEvent* event) {

    if (!inproccess) {

        if (!ticked) {
            bx = event->pos().x();
            by = event->pos().y();
            ticked = 1;
        }

        if (bx >= 377 && bx <= 935 && by >= 93 && by <= 512) {
            ui->choose->setGeometry(bx, by, (event->pos().y() - by) * 1.33, event->pos().y() - by);
        }
    }

}

void MainWindow::mousePressEvent(QMouseEvent* event) {

}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {

    if (!inproccess) {

        ticked = 0;

        double x = std::min(int(bx), int(event->pos().x())) - 375;
        double y = std::min(int(by), int(event->pos().y())) - 90;
        double a = abs(event->pos().x() - bx);
        double b = abs(event->pos().y() - by);

        centeri = x + a / 2.0;
        centerj = y + b / 2.0;

        starti = x / scale + starti;
        startj = startj - y / scale;

        scale *= 480.0 / b;

        buildPic(std::stoi(ui->lineEdit->text().toStdString()));

        ui->choose->setGeometry(-800, -800, 0, 0);
    }
}
