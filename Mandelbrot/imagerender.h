#ifndef IMAGERENDER_H
#define IMAGERENDER_H
#include <string>
#include "QImage"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ImageRender
{
public:
    // CONSTRUCTORS ////////////////
    ImageRender(Ui::MainWindow *&_ui);
    ImageRender(QWidget *add);
    ImageRender(uint16_t _height,
                uint16_t _width,
                uint16_t _x,
                uint16_t _y,
                QString  _PATH,
                Ui::MainWindow *&_ui,
                QWidget *add);
    ~ImageRender();

    // SETTERS /////////////////////
    void setSize(uint16_t _height, uint16_t _width);
    void setPos (uint16_t _x,      uint16_t _y);
    void setPath(QString  _PATH);

    // GETTERS /////////////////////
    uint16_t getHeight();
    uint16_t getWidth();
    uint16_t getX();
    uint16_t getY();
    QString  getPath();

    // FUNCTIONAL //////////////////
    bool render();
    bool render(uint16_t _height, uint16_t _width);
    bool render(uint16_t _height, uint16_t _width,
                uint16_t _x,      uint16_t _y);
    bool render(uint16_t _height, uint16_t _width,
                uint16_t _x,      uint16_t _y,
                QString  _PATH);

private:
    uint16_t       height = 0, width = 0;
    uint16_t       x = 0, y = 0;
    QString        PATH;
    QGraphicsView  *graphicsView = nullptr;
    QGraphicsScene *scene = nullptr;
    QImage         img;
    Ui::MainWindow *ui = nullptr;
    QGraphicsPixmapItem* pixmapItem = nullptr;
};

#endif // IMAGERENDER_H
