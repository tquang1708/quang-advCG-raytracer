/* plane.cpp - Planes, a subclass of objects
 * Quang Tran - 10/16/19
 * */

#include "headers/plane.hpp"

Plane::Plane() {
    //
}

Tuple Plane::normalAt(Tuple point) {
    (void)point;
    Tuple objNormal = Tuple::Vector(0, 1, 0);
    Tuple worldNormal = transform.inverse().transpose() * objNormal;
    worldNormal.setw(0);
    worldNormal = worldNormal.normalize();
    return worldNormal;
}

std::vector<double> Plane::intersect(Ray r){
    std::vector<double> ints;
    Ray worldR = r.transform(transform.inverse());
    if (abs(worldR.getDirection().gety()) < EPSILON) {
        return ints;
    }
    else {
        double t = -(worldR.getOrigin().gety())/(worldR.getDirection().gety());
        ints.push_back(t);
        return ints;
    }
}
