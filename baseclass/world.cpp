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

Color World::shadeHit(const Ray r, const Intersection inter) {
    //preparing
    Object* o = inter.getObject();
    Material m = o -> getMaterial();
    double t = inter.getTime();
    Tuple hit = r.position(t);
    Tuple normalv = o -> normalAt(hit);
    //calculating over point to push point in correct dir
    Tuple hitOver = hit + normalv * EPSILON;
    Tuple eye = r.getOrigin();
    Tuple eyev = -r.getDirection();
    bool shadow = this -> isShadowed(hitOver);

    //checking inside
    if (dot(normalv, eyev) < 0) {
        normalv = -normalv;
    }

    Color c(0, 0, 0);
    //iterate over lights
    for (size_t i = 0; i < lightsArray.size(); i++) {
        PointLight currLight = *lightsArray[i];
        c += lighting(m, currLight, hitOver, normalv, eye, shadow);
    }

    c.clamp();
    return c;
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
                return this -> shadeHit(r, ints[i]);
            }
        }
        return black;
    }
}

bool World::isShadowed(Tuple point) {
    for (size_t i = 0; i < (this -> lightsArray).size(); i++) {
        Tuple temp = lightsArray[i] -> getPosition() - point;
        double distance = temp.magnitude();
        Tuple direction = temp.normalize();

        Ray r(point, direction);
        std::vector<Intersection> ints = this -> intersectWorld(r);

        if (ints.size() == 0) {
            return false;
        } else {
            for (size_t i = 0; i < ints.size(); i++) {
                if (ints[i].getTime() < 0) {
                    return false;
                } else {
                    if (ints[i].getTime() > distance) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
