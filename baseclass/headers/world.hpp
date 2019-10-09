/* world.hpp - header for world - a collection of objects and lights in scene
 * Quang Tran - 10/9/19
 * */

#pragma once

#include "object.hpp"
#include "sphere.hpp"
#include "pointlight.hpp"
#include "ray.hpp"
#include <vector>

class World {
    private:
        std::vector<Object*> objectsArray;
        std::vector<PointLight*> lightsArray;
    public:
        World();
        static World DefaultWorld();

        //adding stuffs funcs
        void addLight(PointLight* pl);
        void addObject(Object* o);

        //world functions
        std::vector<double> intersectWorld(const Ray r);
};

inline World World::DefaultWorld() {
    World defaultWorld;
    static PointLight defaultLight(Tuple::Point(-10, 10, -10), Color(1, 1, 1));
    defaultWorld.addLight(&defaultLight);

    static Sphere s1;
    Material m;
    m.setColor(Color(0.8, 1.0, 0.6));
    m.setDiffuse(0.7);
    m.setSpecular(0.2);
    s1.setMaterial(m);

    static Sphere s2;
    s2.setTransform(Matrix::Scaling(0.5, 0.5, 0.5));

    defaultWorld.addObject(&s1);
    defaultWorld.addObject(&s2);

    return defaultWorld;
}
