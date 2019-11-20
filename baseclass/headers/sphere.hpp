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
        static Sphere GlassSphere();
        std::vector<double> intersect(const Ray r);
        Tuple normalAt(const Tuple point);
};

inline Sphere Sphere::GlassSphere() {
    Sphere s;
    Material m;
    s.setTransform(Matrix::Identity());
    m.setTransparency(1.0);
    m.setRefractiveIndex(1.5);
    s.setMaterial(m);
    return s;
}

#endif
