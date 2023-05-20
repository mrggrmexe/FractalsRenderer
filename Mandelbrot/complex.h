#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <algorithm>
#include <iomanip>


class Complex
{


public:
    Complex();
    Complex(double _x, double _y);

    void addConst(double add);
    void addOther(Complex z);
    void mulOther(Complex z);
    void powPermutation();
    double ro();

    double getX();
    double getY();

    void setX(double _x);
    void setY(double _y);

    void update(double _x, double _y);

private:
    double x, y;

};

#endif // COMPLEX_H
