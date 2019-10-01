/* sphere.hpp - declaration of sphere object - a basic unit sphere
 * Quang Tran - 9/11/2019
 * */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>
#include "ray.hpp"
#include "tuple.hpp"
#include "material.hpp"
#include "matrix.hpp"

class Sphere {
    private:
        static int id_count;
        int id;
        Material material;
        Matrix transform = Matrix::Identity();
    public:
        Sphere();
        std::vector<double> intersect(Ray r);
        Tuple normalAt(Tuple point) const;

        //getter func
        Material getMaterial() const;
        Matrix getTransform() const;

        //setter func
        void setMaterial(Material m);
        void setTransform(Matrix t);
};


#endif
