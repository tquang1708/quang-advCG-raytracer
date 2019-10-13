/* world.cpp - implemenatation of funcs in world
 * Quang Tran - 10/9/19
 * */

#include "headers/world.hpp"
#include "headers/baseclass_funcs.hpp"
#include <algorithm>

World::World() {
}

//adding stuffs funcs
void World::addLight(PointLight* pl) {
    lightsArray.push_back(pl);
}

void World::addObject(Object* o) {
    objectsArray.push_back(o);
}

//getter funcs
Object* World::getObject(int index) const {
    return objectsArray[index];
}

PointLight* World::getLight(int index) const {
    return lightsArray[index];
}

//world functions
std::vector<Intersection> World::intersectWorld(const Ray r) {
    std::vector<Intersection> worldInts;

    for (size_t i = 0; i < objectsArray.size(); i++) {
        std::vector<double> objInts = objectsArray[i] -> intersect(r);
        for (size_t j = 0; j < objInts.size(); j++) {
            worldInts.push_back(Intersection(objInts[j], objectsArray[i]));
        }
    }

    std::sort(worldInts.begin(), worldInts.end());
    return worldInts;
}

Color World::shadeHit(const Ray r, const Intersection inter) const {
    //preparing
    Object* o = inter.getObject();
    double t = inter.getTime();
    Tuple hit = r.position(t);
    Tuple normalv = o -> normalAt(hit);
    Tuple eye = r.getOrigin();
    Tuple eyev = -r.getDirection();

    //checking inside
    if (dot(normalv, eyev) < 0) {
        normalv = -normalv;
    }

    Color c(0, 0, 0);
    //iterate over lights
    for (size_t i = 0; i < lightsArray.size(); i++) {
        PointLight currLight = *lightsArray[i];
        c += lighting(o -> getMaterial(), currLight, hit, normalv, eye);
    }

    c.clamp();
    return c;
}

Color World::colorAt(const Ray r) {
    std::vector<Intersection> ints = this -> intersectWorld(r);
    if (ints.size() == 0) {
        Color black(0, 0, 0);
        return black;
    }
    else {
        //only calculate the color at closest inter
        return this -> shadeHit(r, ints[0]);
    }
}
