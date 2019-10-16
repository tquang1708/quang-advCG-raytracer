/*plane.hpp - header for planes
 * Quang Tran - 10/16/19
 * */

#pragma once

#include "object.hpp"

class Plane : public Object {
    public:
        //default constructor
        Plane();

        Tuple normalAt(Tuple);
        std::vector<double> intersect(Ray);
};
