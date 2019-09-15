/* baseclass_funcs.cpp - functions that interacts with classes
 * in the baseclass folder
 * Quang Tran - 9/7/2019
 * */

#include "baseclass_headers.hpp"
#include "math.h"

//dot product of two vectors
double dot(Tuple a, Tuple b){
    return (a.getx() * b.getx() +
            a.gety() * b.gety() +
            a.getz() * b.getz() +
            a.getw() * b.getw());
}

//cross product of two vectors
Tuple cross(Tuple a, Tuple b){
    Tuple out = Tuple::Vector(a.gety() * b.getz() - a.getz() * b.gety(),
                              a.getz() * b.getx() - a.getx() * b.getz(),
                              a.getx() * b.gety() - a.gety() * b.getx());
    return out;
}

//lighting objects
Color lighting(Material m, PointLight light, Tuple position, Tuple normalv) {
    //
}
