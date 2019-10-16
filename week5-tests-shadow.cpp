#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"

#include <vector>

//TEST_CASE("There is no shadow when nothing is collinear with point and light") {
//    World w = World::DefaultWorld();
//    Tuple p = Tuple::Point(0, 10, 0);
//    REQUIRE(w.isShadowed(p) == false);
//}
//
//TEST_CASE("The shadow when an object is between the point and the light") {
//    World w = World::DefaultWorld();
//    Tuple p = Tuple::Point(10, -10, 10);
//    REQUIRE(w.isShadowed(p) == true);
//}
//
//TEST_CASE("There is no shadow when an object is behind the light") {
//    World w = World::DefaultWorld();
//    Tuple p = Tuple::Point(-20, 20, -20);
//    REQUIRE(w.isShadowed(p) == false);
//}
//
//TEST_CASE("There is no shadow when an object is behind the point") {
//    World w = World::DefaultWorld();
//    Tuple p = Tuple::Point(-2, 2, -2);
//    REQUIRE(w.isShadowed(p) == false);
//}
//
TEST_CASE("shade_hit() is given an intersection in shadow") {
    World w;
    PointLight pl(Tuple::Point(0, 0, -10), Color(1, 1, 1));
    w.addLight(&pl);
    Sphere s1;
    w.addObject(&s1);
    Sphere s2;
    s2.setTransform(Matrix::Translation(0, 0, 10));
    w.addObject(&s2);
    Ray r(Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1));
    Intersection i(4, &s2);
    Color c = w.shadeHit(r, i);
    REQUIRE(c == Color(0.1, 0.1, 0.1));
}
