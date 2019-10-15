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

TEST_CASE("Shading an intersection") {
    World w = World::DefaultWorld();
    Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
    Object* shape = w.getObject(0);
    Intersection i(4, shape);
    Color c = w.shadeHit(r, i);
    REQUIRE(c == Color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("Shading an intersection from the inside") {
    World w = World::DefaultWorld();
    //static PointLight pl(Tuple::Point(0, 0.25, 0), Color(1, 1, 1));
    //w.addLight(&pl);
    Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
    Object* shape = w.getObject(1);
    Intersection i(0.5, shape);
    Color c = w.shadeHit(r, i);
    REQUIRE(c == Color(0.90498, 0.90498, 0.90498));
}

TEST_CASE("The color when a ray misses") {
    World w = World::DefaultWorld();
    Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 1, 0));
    Color c = w.colorAt(r);
    REQUIRE(c == Color(0, 0, 0));
}

TEST_CASE("The color when a ray hits") {
    World w = World::DefaultWorld();
    Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
    Color c = w.colorAt(r);
    REQUIRE(c == Color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("The color with an intersection behind the ray"){
    World w = World::DefaultWorld();
    Object* outer = w.getObject(0);
    Material m1 = outer -> getMaterial();
    m1.setAmbient(1);
    outer -> setMaterial(m1);
    Object* inner = w.getObject(1);
    Material m2 = inner -> getMaterial();
    m2.setAmbient(1);
    inner -> setMaterial(m2);
    Ray r(Tuple::Point(0, 0, 0.75), Tuple::Vector(0, 0, -1));
    Color c = w.colorAt(r);
    REQUIRE(c == inner -> getMaterial().getColor());
}
