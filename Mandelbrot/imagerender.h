#ifndef IMAGERENDER_H
#define IMAGERENDER_H
#include <string>
#include "QImage"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <iostream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ImageRender
{

public:

    // CONSTRUCTORS ////////////////

    ImageRender(Ui::MainWindow    *&_ui);
    ImageRender(QWidget           *add);
    ImageRender(uint16_t          _height,
                uint16_t          _width,
                uint16_t          _x,
                uint16_t          _y,
                QString           _PATH,
                Ui::MainWindow    *&_ui,
                QWidget           *add);

    ////////////////////////////////


    // SETTERS /////////////////////

    void setSize(uint16_t _height, uint16_t _width);
    void setPos (uint16_t _x,      uint16_t _y);
    void setPath(QString  _PATH);

    ////////////////////////////////

    // GETTERS /////////////////////

    uint16_t getHeight();
    uint16_t getWidth();
    uint16_t getX();
    uint16_t getY();
    QString  getPath();

    ////////////////////////////////

    // FUNCTIONAL //////////////////

    // RENDER OVERLOAD
    bool render();
    bool render(uint16_t _height, uint16_t _width);
    bool render(uint16_t _height, uint16_t _width,
                uint16_t _x,      uint16_t _y);
    bool render(uint16_t _height, uint16_t _width,
                uint16_t _x,      uint16_t _y,
                QString  _PATH);

    ////////////////////////////////

private slots:

private:
    uint16_t       height, width;
    uint16_t       x, y;
    QString        PATH;
    QGraphicsView  *graphicsView;
    QGraphicsScene *scene;
    QImage         img;
    Ui::MainWindow *ui;
};

#endif // IMAGERENDER_H

