#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"

#include <vector>

TEST_CASE("The normal of a plane is constant everywhere") {
    Plane p;
    Tuple n1 = p.normalAt(Tuple::Point(0, 0, 0));
    Tuple n2 = p.normalAt(Tuple::Point(10, 0, -10));
    Tuple n3 = p.normalAt(Tuple::Point(-5, 0, 150));
    REQUIRE(n1 == Tuple::Vector(0, 1, 0));
    REQUIRE(n2 == Tuple::Vector(0, 1, 0));
    REQUIRE(n3 == Tuple::Vector(0, 1, 0));
}

TEST_CASE("Intersect with a ray parallel to the plane") {
    Plane p;
    Ray r(Tuple::Point(0, 10, 0), Tuple::Vector(0, 0, 1));
    std::vector<double> xs = p.intersect(r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("Intersect with a coplanar ray") {
    Plane p;
    Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
    std::vector<double> xs = p.intersect(r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray intersecting a plane from above") {
    Plane p;
    Ray r(Tuple::Point(0, 1, 0), Tuple::Vector(0, -1, 0));
    std::vector<double> xs = p.intersect(r);
    REQUIRE(xs.size() == 1);
    REQUIRE(xs[0] == 1);
}

TEST_CASE("A ray intersecting a plane from below") {
    Plane p;
    Ray r(Tuple::Point(0, -1, 0), Tuple::Vector(0, 1, 0));
    std::vector<double> xs = p.intersect(r);
    REQUIRE(xs.size() == 1);
    REQUIRE(xs[0] == 1);
}
