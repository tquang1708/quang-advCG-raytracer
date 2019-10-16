/* plane.cpp - Planes, a subclass of objects
 * Quang Tran - 10/16/19
 * */

#include "headers/plane.hpp"

Plane::Plane() {
    //
}

Tuple Plane::normalAt(Tuple point) {
    (void)point;
    return(Tuple::Vector(0, 1, 0));
}

std::vector<double> Plane::intersect(Ray r){
    std::vector<double> ints;
    if (abs(r.getDirection().gety()) < EPSILON) {
        return ints;
    }
    else {
        double t = -(r.getOrigin().gety())/(r.getDirection().gety());
        ints.push_back(t);
        return ints;
    }
}
