/* sphere.cpp - implementation of functions declared in sphere header
 * Quang Tran - 9/11/2019
 * */

#include <vector>
#include <math.h>

#include "headers/sphere.hpp"
#include "headers/tuple.hpp"
#include "headers/baseclass_funcs.hpp"

Sphere::Sphere() {
}

std::vector<double> Sphere::intersect(const Ray r){
    std::vector<double> intersections;

    //inverse is not const
    Ray r2 = r.transform(transform.inverse());

    //calculating o
    Tuple origin = Tuple::Point(0, 0, 0);
    Tuple o = r2.getOrigin() - origin;

    //calculating a
    double a = dot(r2.getDirection(), r2.getDirection());

    //calculating b
    double b = 2 * dot(r2.getDirection(), o);

    //calculating c
    double c = dot(o, o) - 1;

    //calculating discriminant
    double disc = b * b - 4 * c * a;

    //if disc is negative aka no intersections return empty
    if (disc < 0) {
        return intersections;
    }
    //if disc is 0 then return the same value twice
    else if (disc == 0) {
        double ints = -b / (2 * a);
        intersections.push_back(ints);
        intersections.push_back(ints);
        return intersections;
    }
    //2 intersections case
    else {
        double discsqrt = sqrt(disc);
        double int1 = (-b-discsqrt)/(2*a);
        double int2 = (-b+discsqrt)/(2*a);
        intersections.push_back(int1);
        intersections.push_back(int2);
        return intersections;
    }
}

Tuple Sphere::normalAt(const Tuple point) {
    Tuple objectPoint = transform.inverse() * point;
    Tuple origin = Tuple::Point(0, 0, 0);
    Tuple objNormal = objectPoint - origin;
    Tuple worldNormal = (transform.inverse().transpose() * objNormal);
    worldNormal.setw(0);
    worldNormal = worldNormal.normalize();
    return worldNormal;
}
