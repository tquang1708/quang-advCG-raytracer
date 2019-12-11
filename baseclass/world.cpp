/* world.cpp - implemenatation of funcs in world
 * Quang Tran - 10/9/19
 * */

#include "headers/world.hpp"
#include "headers/baseclass_funcs.hpp"
#include <algorithm>
#include <iostream>

#include <chrono>
#include <random>

World::World() {
}

//adding stuffs funcs
void World::addLight(std::shared_ptr<AreaLight> pl) {
    lightsArray.push_back(pl);
}

void World::addObject(std::shared_ptr<Object> o) {
    objectsArray.push_back(o);
}

//removing stuffs funcs
void World::removeLight(std::shared_ptr<AreaLight> pl) {
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

std::shared_ptr<AreaLight> World::getLight(int index) const {
    return lightsArray[index];
}

//world functions
std::vector<Intersection> World::intersectWorld(const Ray r) {
    std::vector<Intersection> worldInts;

    for (size_t i = 0; i < objectsArray.size(); ++i) {
        std::vector<double> objInts = objectsArray[i] -> intersect(r);
        for (size_t j = 0; j < objInts.size(); ++j) {
            worldInts.push_back(Intersection(objInts[j], objectsArray[i]));
        }
    }

    std::sort(worldInts.begin(), worldInts.end());
    return worldInts;
}


Color World::reflectedColor(const Comps comps, const int remaining) {
    Material m = comps.object -> getMaterial();

    //nonreflective surface
    if (m.getReflectivity() == 0 || remaining == 0) {
        return Color(0, 0, 0);
    }

    //reflected ray
    Ray reflected(comps.over_point, comps.reflectv);
    Color out = colorAt(reflected, remaining - 1) * m.getReflectivity();
    return out;
}

Color World::refractedColor(const Comps comps, int remaining) {
    //opaque obj // reflect over
    std::shared_ptr<Object> o = comps.object;
    Material m = o -> getMaterial();
    if (m.getTransparency() == 0.0 || remaining == 0.0) {
        return Color(0, 0, 0);
    }

    //snell's law for total internal reflection
    double n_ratio = comps.n1 / comps.n2;
    double cos_i = dot(comps.eyev, comps.normalv);
    double sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);

    if (sin2_t > 1.0) {
        return Color(0, 0, 0);
    }

    //calculation
    double cos_t = sqrt(1.0 - sin2_t);
    Tuple direction = comps.normalv * (n_ratio * cos_i - cos_t) -
                      comps.eyev * n_ratio;
    Ray refractedRay(comps.under_point, direction);
    return colorAt(refractedRay, remaining - 1) * m.getTransparency();
}

//lighting objects
bool World::isShadowed(const Tuple lightPos, const Tuple point) {
    Tuple temp = lightPos - point;
    double distance = temp.magnitude();
    Tuple direction = temp.normalize();

    Ray r(point, direction);
    std::vector<Intersection> ints = intersectWorld(r);

    if (ints.size() > 0) {
        for (size_t i = 0; i < ints.size(); ++i) {
            if (ints[i].getTime() > 0) {
                if (ints[i].getTime() < distance) {
                    return true;
                }
            }
        }
    }
    return false;
}

Color World::lighting(const std::shared_ptr<Object> o, const AreaLight light, const Tuple hitPoint, const Tuple normalv, const Tuple eye) {
    Tuple wUnit = (light.lowCorner - light.wCorner) * (1.0 / light.wSteps);
    Tuple hUnit = (light.lowCorner - light.hCorner) * (1.0 / light.hSteps);

    Color out(0, 0, 0);

    //rng
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> dis(0.25, 0.75);

    for (int w = 0; w < light.wSteps; ++w) {
        for (int h = 0; h < light.hSteps; ++h) {
            //determine position of current position in grid
            Tuple position = light.lowCorner + wUnit * (w + dis(generator)) + hUnit * (h + dis(generator));
            position.setw(1.0);

            //determine color at point based on pattern
            Color color;
            Material m = o -> getMaterial();
            if (m.getPattern() == nullptr) {
                color = m.getColor();
            } else {
                color = m.getPattern() -> patternAtObject(o, hitPoint);
            }

            //calculate ambient
            Color ambient = color * light.intensity * m.getAmbient();
            //calculate emission
            Color emission = color * m.getEmission();

            //determine shadow
            bool shadow;
            if (o -> getMaterial().getShadowCast()) {
                shadow = isShadowed(position, hitPoint);
            } else {
                shadow = false;
            }

            //if shadowed return ambient
            if (shadow) {
                out += ambient + emission;
            } else {
                //calculate diffuse
                Tuple unitVectorToLight = (position - hitPoint).normalize();
                double lightIntensity = dot(normalv, unitVectorToLight);

                //black default case
                Color diffuse(0, 0, 0);
                Color specular(0, 0, 0);
                if (lightIntensity > 0) {
                    //calc diffuse if lightInt > 0
                    diffuse = color * light.intensity * lightIntensity * m.getDiffuse();

                    //calculate specular
                    Tuple reflectionVector = (normalv * lightIntensity * 2- unitVectorToLight).normalize();
                    Tuple unitVectorToEye = (eye - hitPoint).normalize();
                    double reflectDotEye = dot(reflectionVector, unitVectorToEye);
                    if (reflectDotEye > 0) {
                        double specularIntensity = pow(reflectDotEye, m.getShininess());
                        specular = light.intensity * specularIntensity * m.getSpecular();
                    }
                }

                //final color
                out += diffuse + emission + specular + ambient;
            }
        }
    }

    out = out * (1.0 / (light.wSteps * light.hSteps));
    out.clamp();

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
    for (size_t i = 0; i < lightsArray.size(); ++i) {
        AreaLight currLight = *lightsArray[i];
        Color main = lighting(o, currLight, hitOver, normalv, eye);
        Color reflected = reflectedColor(comps, remaining);
        Color refracted = refractedColor(comps, remaining);
        if (m.getReflectivity() > 0 && m.getTransparency() > 0) {
            double reflectance = comps.schlick();
            out += main + reflected * reflectance + refracted * (1 - reflectance);
        } else {
            out += main + reflected + refracted;
        }
    }

    out = out * (1.0 / lightsArray.size());
    out.clamp();
    return out;
}

Color World::colorAt(const Ray r, const int remaining) {
    std::vector<Intersection> ints = intersectWorld(r);
    Color black(0, 0, 0);
    if (ints.size() == 0) {
        return black;
    }
    else {
        for (size_t i = 0; i < ints.size(); ++i) {
            if (ints[i].getTime() > 0) {
                return shadeHit(Comps(r, ints[i], ints), remaining);
            }
        }
        return black;
    }
}
