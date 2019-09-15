/* sphere.cpp - implementation of functions declared in sphere header
 * Quang Tran - 9/11/2019
 * */

#include <vector>
#include <math.h>

#include "headers/sphere.hpp"
#include "headers/ray.hpp"
#include "headers/tuple.hpp"
#include "headers/baseclass_funcs.hpp"

//defining static var
int Sphere::id_count = 0;

//giving each sphere an unique id
Sphere::Sphere() {
    id = id_count;
    id_count += 1;
}

std::vector<double> Sphere::intersect(Ray r) const {
    std::vector<double> intersections;

    //calculating o
    Tuple origin = Tuple::Point(0, 0, 0);
    Tuple o = r.getOrigin() - origin;

    //calculating b
    double b = 2 * dot(r.getDirection(), o);

    //calculating c
    double c = dot(o, o) - 1;

    //calculating discriminant
    double disc = b * b - 4 * c;

    //if disc is negative aka no intersections return empty
    if (disc < 0) {
        return intersections;
    }
    //if disc is 0 then return the same value twice
    else if (disc == 0) {
        double ints = -b / 2;
        intersections.push_back(ints);
        intersections.push_back(ints);
        return intersections;
    }
    //2 intersections case
    else {
        double discsqrt = sqrt(disc);
        double int1 = (-b-discsqrt)/2;
        double int2 = (-b+discsqrt)/2;
        intersections.push_back(int1);
        intersections.push_back(int2);
        return intersections;
    }
}

Tuple Sphere::normalAt(Tuple point) const{
    Tuple origin = Tuple::Point(0, 0, 0);
    return (point - origin).normalize();
}
