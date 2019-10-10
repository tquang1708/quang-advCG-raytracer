/* intersection.cpp - implementation of functions in intersection header
 * Quang Tran - 10/9/19
 * */

#include "headers/intersection.hpp"

Intersection::Intersection(double t, Object* o): time(t), object(o) {}

//getter funcs
double Intersection::getTime() const {
    return time;
}

Object Intersection::getObject() const {
    return *object;
}

bool Intersection::operator<(const Intersection &i) const {
    return (time < i.getTime());
}
