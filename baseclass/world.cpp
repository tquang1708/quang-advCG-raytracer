/* world.cpp - implemenatation of funcs in world
 * Quang Tran - 10/9/19
 * */

#include "headers/world.hpp"
#include "headers/baseclass_funcs.hpp"
#include <algorithm>
#include <iostream>

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

double World::isShadowed(PointLight pl, Tuple point) {
    Tuple temp = pl.getPosition() - point;
    double distance = temp.magnitude();
    Tuple direction = temp.normalize();

    Ray r(point, direction);
    std::vector<Intersection> ints = this -> intersectWorld(r);

    if (ints.size() > 0) {
        for (size_t i = 0; i < ints.size(); i++) {
            if (ints[i].getTime() > 0) {
                if (ints[i].getTime() < distance) {
                    return 1.0;
                }
            }
        }
    }
    return 0.0;
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

Color World::refractedColor(const Comps comps, int remaining) {
    //opaque obj // reflect over
    Material m = comps.object -> getMaterial();
    if (m.getTransparency() == 0 || remaining == 0) {
        return Color(0, 0, 0);
    }

    //snell's law for total internal reflection
    double n_ratio = comps.n1 / comps.n2;
    double cos_i = dot(comps.eyev, comps.normalv);
    double sin2_t = n_ratio * n_ratio * (1.0 - cos_i * cos_i);
    if (sin2_t > 1) {
        return Color(0, 0, 0);
    }

    //calculation
    double cos_t = sqrt(1.0 - sin2_t);
    Tuple refractedRay_dir = comps.normalv * (n_ratio * cos_i - cos_t) -
                             comps.eyev * n_ratio;
    Ray refractedRay(comps.under_point, refractedRay_dir);
    Color out = this -> colorAt(refractedRay, remaining - 1) * m.getTransparency();

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
    double shadow;
    //iterate over lights
    for (size_t i = 0; i < lightsArray.size(); i++) {
        PointLight currLight = *lightsArray[i];
        if (m.getShadowCast()) {
            shadow = this -> isShadowed(currLight, hitOver);
        } else {
            shadow = 0.0;
        }
        out += lighting(o, currLight, hitOver, normalv, eye, shadow);
        Color reflected = this -> reflectedColor(comps, remaining);
        Color refracted = this -> refractedColor(comps, remaining);
        if (m.getReflectivity() > 0 && m.getTransparency() > 0) {
            double reflectance = comps.schlick();
            out = out + reflected * reflectance + refracted * (1.0 - reflectance);
        } else {
            out = out + reflected + refracted;
        }
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
