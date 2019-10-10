#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"

#include <vector>

TEST_CASE("Intersect a world with a ray") {
    World w = World::DefaultWorld();
    Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
    std::vector<Intersection> xs = w.intersectWorld(r);
    REQUIRE(xs.size() == 4);
    REQUIRE(xs[0].getTime() == 4);
    REQUIRE(xs[1].getTime() == 4.5);
    REQUIRE(xs[2].getTime() == 5.5);
    REQUIRE(xs[3].getTime() == 6);
}

//TEST_CASE("Shading an intersection") {
//    World w = World::DefaultWorld();
//    Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
//    Object shape = w.getObject(0);
//}
