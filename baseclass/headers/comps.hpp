/* comps.hpp - header for computation storage class
 * Quang Tran - 10/23/19
 * */

#pragma once

#include "intersection.hpp"
#include "ray.hpp"

class Comps {
    public:
        double time;
        std::shared_ptr<Object> object;
        Tuple point;
        Tuple eye;
        Tuple eyev;
        Tuple normalv;
        Tuple reflectv;
        Tuple over_point;
        Tuple under_point;
        double n1;
        double n2;

        //constructors
        Comps(Ray, Intersection, std::vector<Intersection> is = std::vector<Intersection>());

        //schlick_reflectance
        double schlick() const;
};
