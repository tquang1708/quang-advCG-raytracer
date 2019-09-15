/* sphere.hpp - declaration of sphere object - a basic unit sphere
 * Quang Tran - 9/11/2019
 * */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>
#include "ray.hpp"
#include "tuple.hpp"
#include "material.hpp"

class Sphere {
    private:
        static int id_count;
        int id;
        Material material;
    public:
        Sphere();
        std::vector<double> intersect(Ray r) const;
        Tuple normalAt(Tuple point) const;

        //getter func
        Material getMaterial() const;

        //setter func
        void setMaterial(Material m);
};


#endif
