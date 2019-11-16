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

Color World::reflectedColor(const Comps comps, const int remaining) {
    Material m = comps.object -> getMaterial();

    //nonreflective surface
    if (m.getReflectivity() == 0 || remaining == 0) {
        return Color(0, 0, 0);
    }

    //reflected ray
    Ray reflected(comps.over_point, comps.reflectv);
    Color out = this -> colorAt(reflected, remaining - 1) * m.getReflectivity();
    return out;
}

Color World::shadeHit(const Comps comps, const int remaining) {
    //preparing
    std::shared_ptr<Object> o = comps.object;
    Material m = o -> getMaterial();
    Tuple normalv = comps.normalv;
    Tuple hitOver = comps.over_point;
    Tuple eye = comps.eye;

    Color out(0, 0, 0);
    //iterate over lights
    for (size_t i = 0; i < lightsArray.size(); i++) {
        PointLight currLight = *lightsArray[i];
        bool shadow = this -> isShadowed(currLight, hitOver);
        out += lighting(m, currLight, hitOver, normalv, eye, shadow);
        out += this -> reflectedColor(comps, remaining);
    }

    out.clamp();
    return out;
}

Color World::colorAt(const Ray r, const int remaining) {
    std::vector<Intersection> ints = this -> intersectWorld(r);
    Color black(0, 0, 0);
    if (ints.size() == 0) {
        return black;
    }
    else {
        for (size_t i = 0; i < ints.size(); i++) {
            if (ints[i].getTime() > 0) {
                return this -> shadeHit(Comps(r, ints[i]), remaining);
            }
        }
        return black;
    }
}
