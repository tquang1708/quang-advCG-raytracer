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
        Color reflectedColor(const Comps);
        Color shadeHit(const Comps);
        Color colorAt(const Ray r);
};
