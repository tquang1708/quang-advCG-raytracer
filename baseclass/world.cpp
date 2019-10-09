/* world.cpp - implemenatation of funcs in world
 * Quang Tran - 10/9/19
 * */

#include "headers/world.hpp"
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

//world functions
std::vector<double> World::intersectWorld(const Ray r){
    std::vector<double> worldInts;

    for (size_t i = 0; i < objectsArray.size(); i++) {
        std::vector<double> objInts = objectsArray[i] -> intersect(r);
        worldInts.insert(worldInts.end(), objInts.begin(), objInts.end());
    }

    std::sort(worldInts.begin(), worldInts.end());
    return worldInts;
}
