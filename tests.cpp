#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"

/*
TEST_CASE("Reflectivity for the default material") {
    Material m;
    REQUIRE(m.getReflectivity()== 0.0);
}*/

/*
TEST_CASE("Precomp reflection vect") {
    std::shared_ptr<Plane> shape = std::make_shared<Plane>();
    Ray r(Tuple::Point(0, 1, -1), Tuple::Vector(0, -sqrt(2)/2, sqrt(2)/2));
    Intersection i(sqrt(2), shape);
    Comps c(r, i);
    REQUIRE(c.reflectv == Tuple::Vector(0, sqrt(2)/2, sqrt(2)/2));
}*/

/*
TEST_CASE("The reflected color for a nonreflective material") {
    World w = World::DefaultWorld();
    Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
    std::shared_ptr<Sphere> shape = std::dynamic_pointer_cast<Sphere>(w.getObject(1));
    Material m = shape-> getMaterial();
    m.setAmbient(1);
    shape -> setMaterial(m);
    Intersection i(1, shape);
    Comps c(r, i);
    Color co = w.reflectedColor(c);
    REQUIRE(co == Color(0, 0, 0));
}*/

/* correct
TEST_CASE("The reflected color for a reflective material") {
    World w = World::DefaultWorld();
    std::shared_ptr<Plane> shape = std::make_shared<Plane>();
    Material m;
    m.setReflectivity(0.5);
    shape -> setTransform(Matrix::Translation(0, -1, 0));
    shape -> setMaterial(m);
    w.addObject(shape);
    Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, -sqrt(2)/2, sqrt(2)/2));
    Intersection i(sqrt(2), shape);
    Comps co(r, i);
    Color c = w.reflectedColor(co);
    REQUIRE(c == Color(0.19032, 0.2379, 0.14274));
}*/

/*correct
TEST_CASE("shadehit") {
    World w = World::DefaultWorld();
    std::shared_ptr<Plane> shape = std::make_shared<Plane>();
    Material m;
    m.setReflectivity(0.5);
    shape -> setTransform(Matrix::Translation(0, -1, 0));
    shape -> setMaterial(m);
    w.addObject(shape);
    Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, -sqrt(2)/2, sqrt(2)/2));
    Intersection i(sqrt(2), shape);
    Comps co(r, i);
    Color c = w.shadeHit(co);
    REQUIRE(c == Color(0.87677, 0.92436, 0.82918));
}*/

TEST_CASE("recursion") {
    World w;
    w.addLight(std::make_shared<PointLight>(Tuple::Point(0, 0, 0), Color(1, 1, 1)));
    Material p1;
    p1.setReflectivity(1);
    std::shared_ptr<Plane> lower = std::make_shared<Plane>();
    lower -> setMaterial(p1);
    lower -> setTransform(Matrix::Translation(0, -1, 0));
    Material p2;
    p2.setReflectivity(1);
    std::shared_ptr<Plane> upper = std::make_shared<Plane>();
    lower -> setMaterial(p2);
    lower -> setTransform(Matrix::Translation(0, 1, 0));
    w.addObject(lower);
    w.addObject(upper);
    Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 1, 0));
    Color c = w.colorAt(r, 10);
    REQUIRE(true);
}

TEST_CASE("limit") {
    World w = World::DefaultWorld();
    std::shared_ptr<Plane> shape = std::make_shared<Plane>();
    Material m;
    m.setReflectivity(0.5);
    shape -> setTransform(Matrix::Translation(0, -1, 0));
    shape -> setMaterial(m);
    w.addObject(shape);
    Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, -sqrt(2)/2, sqrt(2)/2));
    Intersection i(sqrt(2), shape);
    Comps co(r, i);
    Color c = w.reflectedColor(co, 0);
    REQUIRE(c == Color(0, 0, 0));
}
