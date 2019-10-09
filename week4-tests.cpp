#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"

#include <vector>

TEST_CASE("Intersect a world with a ray") {
    World w = World::DefaultWorld();
    Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
    std::vector<double> xs = w.intersectWorld(r);
    REQUIRE(xs.size() == 4);
    REQUIRE(xs[0] == 4);
    REQUIRE(xs[1] == 4.5);
    REQUIRE(xs[2] == 5.5);
    REQUIRE(xs[3] == 6);
}
