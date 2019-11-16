/* world.hpp - header for world - a collection of objects and lights in scene
 * Quang Tran - 10/9/19
 * */

#pragma once

#include "object.hpp"
#include "sphere.hpp"
#include "pointlight.hpp"
#include "ray.hpp"
#include "intersection.hpp"
#include "comps.hpp"
#include <vector>
#include <memory>

class World {
    private:
        std::vector<std::shared_ptr<Object>> objectsArray;
        std::vector<std::shared_ptr<PointLight>> lightsArray;
    public:
        World();
        static World DefaultWorld();

        //adding stuffs funcs
        void addLight(std::shared_ptr<PointLight>);
        void addObject(std::shared_ptr<Object>);

        //removing stuffs funcs
        void removeLight(std::shared_ptr<PointLight>);
        void removeObject(std::shared_ptr<Object>);

        //getter funcs
        std::shared_ptr<Object> getObject(int) const;
        std::shared_ptr<PointLight> getLight(int) const;

        //world functions
        std::vector<Intersection> intersectWorld(const Ray r);
        bool isShadowed(PointLight, Tuple);
        Color reflectedColor(const Comps, const int remaining);
        Color shadeHit(const Comps, const int remaining);
        Color colorAt(const Ray r, const int remaining);
};

inline World World::DefaultWorld() {
    World defaultWorld;
    std::shared_ptr<PointLight> defaultLight = std::make_shared<PointLight>(Tuple::Point(-10, 10, -10), Color(1, 1, 1));
    defaultWorld.addLight(defaultLight);

    std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>();
    Material m;
    Color c(0.8, 1.0, 0.6);
    m.setColor(c);
    m.setDiffuse(0.7);
    m.setSpecular(0.2);
    s1 -> setMaterial(m);

    std::shared_ptr<Sphere> s2 = std::make_shared<Sphere>();
    //Material m2;
    //Color c2(1, 0, 0);
    //m2.setColor(c2);
    //s2.setMaterial(m2);
    s2 -> setTransform(Matrix::Scaling(0.5, 0.5, 0.5));

    defaultWorld.addObject(s1);
    defaultWorld.addObject(s2);

    return defaultWorld;
}
