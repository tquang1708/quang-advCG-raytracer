/* comps.cpp - implementation of computation functions
 * Quang Tran - 10/23/19
 * */

#include "headers/comps.hpp"
#include "headers/baseclass_funcs.hpp"

//constructor
Comps::Comps(Ray r, Intersection i) {
    time = i.getTime();
    object = i.getObject();
    point = r.position(time);
    eye = r.getOrigin();
    eyev = -r.getDirection();
    normalv = object -> normalAt(point);
    over_point = point + normalv * EPSILON;
    under_point = point - normalv * EPSILON;

    //checking inside
    if (dot(normalv, eyev) < 0) {
        normalv = -normalv;
    }

    reflectv = r.getDirection() - normalv * 2 * dot(r.getDirection(), normalv);
}
