#include "imagerender.h"


// CONSTRUCTORS /////////////////////////////////

ImageRender::ImageRender(Ui::MainWindow *&_ui)
    : ui(_ui)
{
    graphicsView = new QGraphicsView;
    scene        = new QGraphicsScene;
}

ImageRender::ImageRender(uint16_t       _height,
                         uint16_t       _width,
                         uint16_t       _x,
                         uint16_t       _y,
                         QString        _PATH,
                         Ui::MainWindow *&_ui,
                         QWidget        *add)
    : height(_height), width(_width),
      x(_x), y(_y),
      PATH(_PATH),
      ui(_ui)
{
    graphicsView = new QGraphicsView(add);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene        = new QGraphicsScene(add);
    render();
}

ImageRender::ImageRender(QWidget *add)
{
    graphicsView = new QGraphicsView(add);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene        = new QGraphicsScene(add);
}

/////////////////////////////////////////////////


// SETTERS //////////////////////////////////////

void ImageRender::setSize(uint16_t _height, uint16_t _width)
{
    height = _height;
    width  = _width;
}

void ImageRender::setPos(uint16_t _x, uint16_t _y)
{
    x = _x;
    y = _y;
}

void ImageRender::setPath(QString _PATH)
{
    PATH = _PATH;
}

/////////////////////////////////////////////////


// GETTERS //////////////////////////////////////

uint16_t ImageRender::getHeight()
{
    return height;
}

uint16_t ImageRender::getWidth()
{
    return width;
}

uint16_t ImageRender::getX()
{
    return x;
}

uint16_t ImageRender::getY()
{
    return y;
}

QString ImageRender::getPath()
{
    return PATH;
}

/////////////////////////////////////////////////


// FUNCTIONAL ///////////////////////////////////

bool ImageRender::render()
{
    if (!img.load(PATH)) return 0;
    img = img.scaled(height, width,
                     Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation);


    QPixmap pixmap = QPixmap::fromImage(img);
    graphicsView->setGeometry(x, y, height, width);
    graphicsView->setStyleSheet("background: transparent");
    graphicsView->setFrameShape(QFrame::NoFrame);
    scene->addPixmap(pixmap);


    graphicsView->setScene(scene);
    graphicsView->show();
    return 1;
}

bool ImageRender::render(uint16_t _height, uint16_t _width)
{
    height = _height;
    width  = _width;
    return this->render();
}

bool ImageRender::render(uint16_t _height, uint16_t _width,
                         uint16_t _x,      uint16_t _y)
{
    height = _height;
    width  = _width;
    x      = _x;
    y      = _y;
    return this->render();
}

bool ImageRender::render(uint16_t _height, uint16_t _width,
                         uint16_t _x,      uint16_t _y,
                         QString  _PATH)
{
    height = _height;
    width  = _width;
    x      = _x;
    y      = _y;
    PATH   = _PATH;
    return this->render();
}

/////////////////////////////////////////////////


