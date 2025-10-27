#include "imagerender.h"
#include <QPainter>

static void tuneView(QGraphicsView* v) {
    if (!v) return;
    v->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    v->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    v->setFrameShape(QFrame::NoFrame);
    v->setRenderHint(QPainter::SmoothPixmapTransform, true);
    v->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}

// CONSTRUCTORS /////////////////////////////////

ImageRender::ImageRender(Ui::MainWindow *&_ui)
    : ui(_ui)
{
    graphicsView = new QGraphicsView;
    scene        = new QGraphicsScene;
    tuneView(graphicsView);
    graphicsView->setScene(scene);
}

ImageRender::ImageRender(uint16_t _height,
                         uint16_t _width,
                         uint16_t _x,
                         uint16_t _y,
                         QString  _PATH,
                         Ui::MainWindow *&_ui,
                         QWidget *add)
    : height(_height), width(_width),
    x(_x), y(_y),
    PATH(_PATH),
    ui(_ui)
{
    graphicsView = new QGraphicsView(add);
    scene        = new QGraphicsScene(add);
    tuneView(graphicsView);
    graphicsView->setScene(scene);
    render();
}

ImageRender::ImageRender(QWidget *add)
{
    graphicsView = new QGraphicsView(add);
    scene        = new QGraphicsScene(add);
    tuneView(graphicsView);
    graphicsView->setScene(scene);
}

ImageRender::~ImageRender()
{
    if (graphicsView && !graphicsView->parent()) {
        delete graphicsView;
        graphicsView = nullptr;
    }
    if (scene && !scene->parent()) {
        delete scene;
        scene = nullptr;
    }
}

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

// GETTERS //////////////////////////////////////

uint16_t ImageRender::getHeight() { return height; }
uint16_t ImageRender::getWidth()  { return width;  }
uint16_t ImageRender::getX()      { return x;      }
uint16_t ImageRender::getY()      { return y;      }
QString  ImageRender::getPath()   { return PATH;   }

// FUNCTIONAL ///////////////////////////////////

bool ImageRender::render()
{
    if (height == 0 || width == 0) return false;

    if (!img.load(PATH)) return false;

    img = img.scaled(height, width,
                     Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation);

    QPixmap pixmap = QPixmap::fromImage(img);

    graphicsView->setGeometry(x, y, height, width);
    graphicsView->setStyleSheet("background: transparent");

    if (!pixmapItem) {
        pixmapItem = scene->addPixmap(pixmap);
        pixmapItem->setTransformationMode(Qt::SmoothTransformation);
        pixmapItem->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
        pixmapItem->setPos(0, 0);
    } else {
        pixmapItem->setPixmap(pixmap);
    }
    scene->setSceneRect(pixmapItem->boundingRect());
    graphicsView->setScene(scene);
    graphicsView->show();
    return true;
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
