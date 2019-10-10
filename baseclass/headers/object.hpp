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

        //disable clang warnings
        //https://useyourloaf.com/blog/disabling-clang-compiler-warnings/
        //virtual func
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type"
        virtual std::vector<double> intersect(Ray r){};
        virtual Tuple normalAt(Tuple point){};
#pragma clang diagnostic pop
};
