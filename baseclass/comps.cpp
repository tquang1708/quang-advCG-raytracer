/* comps.cpp - implementation of computation functions
 * Quang Tran - 10/23/19
 * */

#include "headers/comps.hpp"
#include "headers/baseclass_funcs.hpp"
#include <algorithm>

//constructor
Comps::Comps(Ray r, Intersection i, std::vector<Intersection> is) {
    if (is.size() == 0) {
        is.push_back(i);
    }

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

    //n1n2
    std::vector<std::shared_ptr<Object>> containers;
    for (size_t k = 0; k < is.size(); k++) {
        //entering index
        if (i == is[k]) {
            if (containers.empty()) {
                n1 = 1.0;
            } else {
                n1 = containers.back() -> getMaterial().getRefractiveIndex();
            }
        }

        //determining whether ray entering or exiting object
        if (std::find(containers.begin(), containers.end(), is[k].getObject()) != containers.end()) {
            containers.erase(std::remove(containers.begin(), containers.end(), is[k].getObject()), containers.end());
        } else {
            containers.push_back(is[k].getObject());
        }

        //exiting index
        if (i == is[k]) {
            if (containers.empty()) {
                n2 = 1.0;
            } else {
                n2 = containers.back() -> getMaterial().getRefractiveIndex();
            }
            break;
        }
    }
}

double Comps::schlick() const {
    //schlick_reflectance
    double cosEN = dot(eyev, normalv);
    if (n1 > n2) {
        double n = n1 / n2;
        double sin2_t = n *n * (1.0 - cosEN * cosEN);
        if (sin2_t > 1.0) {
            return 1.0;
        }

        double cos_t = sqrt(1.0 - sin2_t);
        //use cos_t when n1 > n2
        cosEN = cos_t;
    }

    double r0 = (n1 - n2) / ((n1 + n2) * (n1 + n2));

    return r0 + (1 - r0) * pow(1 - cosEN, 5);
}
