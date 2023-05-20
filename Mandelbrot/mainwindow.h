#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include "imagerender.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void buildPic(short n);



private slots:
    void on_application_open();

    void on_pushButton_clicked();

    void on_pushButton_pressed();

    void on_pushButton_released();

    void play_animation();

protected:
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
