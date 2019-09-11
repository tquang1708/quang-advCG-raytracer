/* sphere.hpp - declaration of sphere object - a basic unit sphere
 * Quang Tran - 9/11/2019
 * */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>
#include "ray.hpp"

class Sphere {
    private:
        static int id_count;
        int id;
    public:
        Sphere();
        std::vector<double> intersect(Ray r) const;
};


#endif
