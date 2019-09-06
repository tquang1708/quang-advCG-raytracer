/* color.cpp - implementation of functions defined in color.h
 *
 * Quang Tran - 9/6/2019
 * */

#include "headers/color.hpp"

//default constructor
color::color() {
    x = 0;
    y = 0;
    z = 0;
}

//basic constructor
color::color(double red_, double green_, double blue_) {
    x = red_;
    y = green_;
    z = blue_;
}

//getter functions
double color::getR() const {
    return x;
}

double color::getG() const {
    return y;
}

double color::getB() const {
    return z;
}

//operator * overloading
color color::operator*(const color &a) {
    color out(x * a.getx(), y * a.gety(), z * a.getz());
    return out;
}

//operator * overloading for scalar multiplication
color color::operator*(const double &scalar) {
    color out(x * scalar, y * scalar, z * scalar);
    return out;
}
