#include "complex.h"

Complex::Complex()
{

}

Complex::Complex(double _x, double _y)
    : x(_x), y(_y) {}


void Complex::update(double _x, double _y) {

    x = _x; y = _y;
}

void Complex::setX(double _x) {

    x = _x;
}

void Complex::setY(double _y) {

    y = _y;
}

double Complex::getX() {

    return this->x;
}

double Complex::getY() {

    return this->y;
}


// ОПЕРАЦИИ /////

void Complex::addConst(double add) {

    x += add;
}

void Complex::addOther(Complex z) {

    x += z.getX();
    y += z.getY();
}

void Complex::mulOther(Complex z) {

    double tmp = x;

    x = x * z.getX() - y * z.getY();
    y = tmp * z.getY() + y * z.getX();
}

double Complex::ro() {

    return sqrt(this->x * this->x + this->y * this->y);
}

void Complex::powPermutation() {

    double tmp = x;

     x = x * x - y * y;
     y = tmp * y + y * tmp;

}

/////////////////
