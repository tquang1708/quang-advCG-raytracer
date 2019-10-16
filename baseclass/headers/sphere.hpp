/* sphere.hpp - declaration of sphere object - a basic unit sphere
 * Quang Tran - 9/11/2019
 * */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>
#include "ray.hpp"
#include "object.hpp"

class Sphere : public Object {
    public:
        Sphere();
        std::vector<double> intersect(const Ray r);
        Tuple normalAt(const Tuple point);
};

#endif
