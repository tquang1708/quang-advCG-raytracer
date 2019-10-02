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
Color::Color(double red, double green, double blue) {
    x = red;
    y = green;
    z = blue;
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
Color Color::operator*(const Color &a) const{
    Color out(x * a.getx(), y * a.gety(), z * a.getz());
    return out;
}

//operator * overloading for scalar multiplication
Color Color::operator*(const double &scalar) const{
    Color out(x * scalar, y * scalar, z * scalar);
    return out;
}

//operator + overload specifically for colors
Color Color::operator+(const Color &a) const {
    Color out(x + a.getR(), y + a.getG(), z + a.getB());
    return out;
}

//color clamping
void Color::clamp() {
    x > 1 ? x = 1 : x;
    x < 0 ? x = 0 : x;
    y > 1 ? y = 1 : y;
    y < 0 ? y = 0 : y;
    z > 1 ? z = 1 : z;
    z < 0 ? z = 0 : z;
}
