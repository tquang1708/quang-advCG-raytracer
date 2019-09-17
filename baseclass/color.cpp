/* color.cpp - implementation of functions defined in color.h
 *
 * Quang Tran - 9/6/2019
 * */

#include "headers/color.hpp"

//default constructor
Color::Color() {
    x = 0;
    y = 0;
    z = 0;
}

//basic constructor
Color::Color(double red_, double green_, double blue_) {
    x = red_;
    y = green_;
    z = blue_;
}

//getter functions
double Color::getR() const {
    return x;
}

double Color::getG() const {
    return y;
}

double Color::getB() const {
    return z;
}

//setter funcs
void Color::setR(const double newR) {
    x = newR;
}
void Color::setG(const double newG) {
    y = newG;
}
void Color::setB(const double newB) {
    z = newB;
}

//operator * overloading
Color Color::operator*(const Color &a) {
    Color out(x * a.getx(), y * a.gety(), z * a.getz());
    return out;
}

//operator * overloading for scalar multiplication
Color Color::operator*(const double &scalar) {
    Color out(x * scalar, y * scalar, z * scalar);
    return out;
}
