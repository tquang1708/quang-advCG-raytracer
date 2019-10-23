/* triangle.hpp - header for triangle shape implementation
 * Quang Tran - 10/23/19
 * */

#pragma once

#include "object.hpp"
#include "tuple.hpp"
#include "ray.hpp"
#include <vector>

class Triangle : public Object {
    private:
        Tuple point_a;
        Tuple point_b;
        Tuple point_c;
    public:
        Triangle(Tuple, Tuple, Tuple);
        std::vector<double> intersect(const Ray r);
        Tuple normalAt(const Tuple point);
};
