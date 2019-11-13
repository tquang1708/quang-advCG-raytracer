/* world.cpp - implemenatation of funcs in world
 * Quang Tran - 10/9/19
 * */

#include "headers/world.hpp"
#include "headers/baseclass_funcs.hpp"
#include <algorithm>

World::World() {
}

//adding stuffs funcs
void World::addLight(std::shared_ptr<PointLight> pl) {
    lightsArray.push_back(pl);
}

void World::addObject(std::shared_ptr<Object> o) {
    objectsArray.push_back(o);
}

//removing stuffs funcs
void World::removeLight(std::shared_ptr<PointLight> pl) {
    lightsArray.erase((std::remove(lightsArray.begin(), lightsArray.end(), pl)),
                      lightsArray.end());
}

void World::removeObject(std::shared_ptr<Object> o) {
    objectsArray.erase((std::remove(objectsArray.begin(), objectsArray.end(), o)),
                      objectsArray.end());
}

//getter funcs
std::shared_ptr<Object> World::getObject(int index) const {
    return objectsArray[index];
}

std::shared_ptr<PointLight> World::getLight(int index) const {
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

bool World::isShadowed(PointLight pl, Tuple point) {
    Tuple temp = pl.getPosition() - point;
    double distance = temp.magnitude();
    Tuple direction = temp.normalize();

    Ray r(point, direction);
    std::vector<Intersection> ints = this -> intersectWorld(r);

    if (ints.size() > 0) {
        for (size_t i = 0; i < ints.size(); i++) {
            if (ints[i].getTime() > 0) {
                if (ints[i].getTime() < distance) {
                    return true;
                }
            }
        }
    }
    return false;
}

Color World::reflectedColor(const Comps c) {
    Material m = c.object -> getMaterial();

    //nonreflective surface
    if (m.getReflectivity() == 0) {
        return Color(0, 0, 0);
    }
}

Color World::shadeHit(const Comps c) {
    //preparing
    std::shared_ptr<Object> o = c.object;
    Material m = o -> getMaterial();
    Tuple normalv = c.normalv;
    Tuple hitOver = c.over_point;
    Tuple eye = c.eye;

    Color out(0, 0, 0);
    //iterate over lights
    for (size_t i = 0; i < lightsArray.size(); i++) {
        PointLight currLight = *lightsArray[i];
        bool shadow = this -> isShadowed(currLight, hitOver);
        out += lighting(m, currLight, hitOver, normalv, eye, shadow);
    }

    out.clamp();
    return out;
}

Color World::colorAt(const Ray r) {
    std::vector<Intersection> ints = this -> intersectWorld(r);
    Color black(0, 0, 0);
    if (ints.size() == 0) {
        return black;
    }
    else {
        for (size_t i = 0; i < ints.size(); i++) {
            if (ints[i].getTime() > 0) {
                return this -> shadeHit(Comps(r, ints[i]));
            }
        }
        return black;
    }
}
