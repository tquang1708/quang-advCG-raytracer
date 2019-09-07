/* ray.cpp - implementation of the ray functions defined in the header
 * Quang Tran - 9/7/2019
 * */

#include "headers/ray.hpp"
#include "headers/tuple.hpp"


//basic implementation of constructos
Ray::Ray() {
    origin = Tuple();
    direction = Tuple();
}

Ray::Ray(Tuple origin_, Tuple direction_) {
    origin = origin_;
    direction = direction_;
}

//basic getter functions implementation
Tuple Ray::getOrigin() const{
    return origin;
}

Tuple Ray::getDirection() const{
    return direction;
}

//other functions
//find the position of ray's origin after time following direction
Tuple Ray::position(double time) const{
    Tuple out = origin + direction * time;
    return out;
}
