/* tuple.cpp - implementation for tuple.h header
 * Quang Tran - 9/4/2019
 * */

#include "tuple.h"
#include "math.h"


//basic constructor
tuple::tuple(double x_, double y_, double z_, double w_) {
    x = x_;
    y = y_;
    z = z_;
    w = w_;
}

//point
tuple tuple::point(double x_, double y_, double z_) {
    return tuple(x_, y_, z_, 1.0);
}

//vector
tuple tuple::vector(double x_, double y_, double z_) {
    return tuple(x_, y_, z_, 0.0);
}

//getter functions
double tuple::getx() const{
    return x;
}
double tuple::gety() const{
    return y;
}
double tuple::getz() const{
    return z;
}
double tuple::getw() const{
    return w;
}

//isPoint check
bool tuple::isPoint() {
    if (w == 0.0) return false;
    else return true;
}

//isVector check
bool tuple::isVector() {
    if (w == 1.0) return false;
    else return true;
}

//operator == overloading
bool tuple::operator==(const tuple &a) const{
    if ((abs(x - a.x) <= EPSILON) &&
        (abs(y - a.y) <= EPSILON) &&
        (abs(z - a.z) <= EPSILON) &&
        (abs(w - a.w) <= EPSILON)) {
        return true;
    }
    else return false;
}

//operator + overloading
tuple tuple::operator+(const tuple &a) {
    tuple out(x + a.x, y + a.y, z + a.z, w + a.w);
    return out;
}

//operator - overloading
tuple tuple::operator-(const tuple &a) {
    tuple out(x - a.x, y - a.y, z - a.z, w - a.w);
    return out;
}

//operator negate overloading
tuple tuple::operator-() {
    tuple out(-x, -y, -z, -w);
    return out;
}

//operator assignment overloading
tuple& tuple::operator=(const tuple &a) {
    //cheking for self-assignment
    if (this == &a) {
        return *this;
    }

    this -> x = a.x;
    this -> y = a.y;
    this -> z = a.z;
    this -> w = a.w;
    return *this;
}

//operator * overload
tuple tuple::operator*(const double &scalar) {
    tuple out(x * scalar,
              y * scalar,
              z * scalar,
              w * scalar);
    return out;
}

//operator / overload
tuple tuple::operator/(const double &scalar) {
    tuple out = *this * (1 / scalar);
    return out;
}

