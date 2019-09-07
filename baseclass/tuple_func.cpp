//Tuple_func.cpp - collection of Tuple functions like dot and cross products
//
//Quang Tran - 9/5/2019

#include "headers/tuple.hpp"
#include "headers/tuple_func.hpp"
#include "math.h"

//calculations
//finds magnitude of vector
double magnitude(Tuple a) {
    double out = sqrt(a.getx() * a.getx() +
                      a.gety() * a.gety() +
                      a.getz() * a.getz());
    return out;
}

//normalize a vector (magn = 1)
Tuple normalize(Tuple a) {
    double mag = magnitude(a);
    return Tuple(a.getx() / mag, a.gety() / mag, a.getz() / mag, 0.0);
}

//dot product of two vectors
double dot(Tuple a, Tuple b) {
    return (a.getx() * b.getx() +
            a.gety() * b.gety() +
            a.getz() * b.getz() +
            a.getw() * b.getw());
}

//cross product of two vectors
Tuple cross(Tuple a, Tuple b) {
    Tuple out = Tuple::Vector(a.gety() * b.getz() - a.getz() * b.gety(),
                              a.getz() * b.getx() - a.getx() * b.getz(),
                              a.getx() * b.gety() - a.gety() * b.getx());
    return out;
}
