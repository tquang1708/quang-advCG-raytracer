/* object.hpp - header file for objects
 * Quang Tran - 10/9/19
 * */

#pragma once

#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include <vector>

class Object{
    protected:
        Material material;
        Matrix transform;
    public:
        Object();

        //getter func
        Material getMaterial() const;
        Matrix getTransform() const;

        //setter func
        void setMaterial(Material m);
        void setTransform(Matrix t);

        //virtual func
        virtual std::vector<double> intersect(Ray r){};
        virtual Tuple normalAt(Tuple point){};
};
