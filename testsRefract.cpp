#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"

TEST_CASE("new material stuffs") {
    Material m;
    REQUIRE (m.getTransparency() == 0.0);
    REQUIRE (m.getRefractiveIndex() == 1.0);
}

TEST_CASE("glass sphere") {
    Sphere s = Sphere::GlassSphere();
    REQUIRE (s.getTransform() == Matrix::Identity());
    REQUIRE (s.getMaterial().getTransparency() == 1.0);
    REQUIRE (s.getMaterial().getRefractiveIndex() == 1.5);
}

TEST_CASE("n1n2 inter in comp") {
    std::shared_ptr<Sphere> a = std::make_shared<Sphere>(Sphere::GlassSphere());
    a -> setTransform(Matrix::Scaling(2, 2, 2));
    a -> setMaterial(a -> getMaterial().setRefractiveIndex(1.5));

    std::shared_ptr<Sphere> b = std::make_shared<Sphere>(Sphere::GlassSphere());
    b -> setTransform(Matrix::Translation(0, 0, -0.25));
    b -> setMaterial(b -> getMaterial().setRefractiveIndex(2.0));

    std::shared_ptr<Sphere> c = std::make_shared<Sphere>(Sphere::GlassSphere());
    c -> setTransform(Matrix::Translation(0, 0, 0.25));
    c -> setMaterial(c -> getMaterial().setRefractiveIndex(2.5));

    Ray r(Tuple::Point(0,0,-4), Tuple::Vector(0,0,1));
    std::vector<Intersection> ints;
    ints.push_back(Intersection(2, a));
    ints.push_back(Intersection(2.75, b));
    ints.push_back(Intersection(3.25, c));
    ints.push_back(Intersection(4.75, b));
    ints.push_back(Intersection(5.25, c));
    ints.push_back(Intersection(6, a));
    for (int i = 0; i < 6; i++) {
        Comps c(r, ints[i], ints);
        if (i == 0) {
            REQUIRE((c.n1 == 1.0 && c.n2 == 1.5));
        }
        else if (i == 1) {
            REQUIRE((c.n1 == 1.5 && c.n2 == 2.0));
        }
        else if (i == 2) {
            REQUIRE((c.n1 == 2.0 && c.n2 == 2.5));
        }
        else if (i == 3) {
            REQUIRE((c.n1 == 2.5 && c.n2 == 2.5));
        }
        else if (i == 4) {
            REQUIRE((c.n1 == 2.5 && c.n2 == 1.5));
        }
        else {
            REQUIRE((c.n1 == 1.5 && c.n2 == 1.0));
        }
    }
}

TEST_CASE("underpoint") {
    Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
    std::shared_ptr<Sphere> shape = std::make_shared<Sphere>(Sphere::GlassSphere());
    shape -> setTransform(Matrix::Translation(0, 0, 1));
    Intersection i(5, shape);
    Comps c(r, i);
    REQUIRE(c.under_point.getz() > EPSILON/2);
    REQUIRE(c.point.getz() < c.under_point.getz());
}

TEST_CASE("refracted color - opaque") {
    World w = World::DefaultWorld();
    std::shared_ptr<Sphere> shape = std::dynamic_pointer_cast<Sphere>(w.getObject(0));
    Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
    std::vector<Intersection> xs {Intersection(4, shape), Intersection(6, shape)};
    Comps comps(r, xs[0], xs);
    Color c = w.refractedColor(comps, 5);
    REQUIRE (c == Color(0, 0, 0));
}

TEST_CASE("refracted color - recur depth") {
    World w = World::DefaultWorld();
    std::shared_ptr<Sphere> shape = std::dynamic_pointer_cast<Sphere>(w.getObject(0));
    Material newmat = shape -> getMaterial();
    newmat.setTransparency(1.0);
    newmat.setRefractiveIndex(1.5);
    shape -> setMaterial(newmat);
    Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
    std::vector<Intersection> xs {Intersection(4, shape), Intersection(6, shape)};
    Comps comps(r, xs[0], xs);
    Color c = w.refractedColor(comps, 0);
    REQUIRE (c == Color(0, 0, 0));
}

TEST_CASE("refracted color - total internal reflection") {
    World w = World::DefaultWorld();
    std::shared_ptr<Sphere> shape = std::dynamic_pointer_cast<Sphere>(w.getObject(0));
    Material newmat = shape -> getMaterial();
    newmat.setTransparency(1.0);
    newmat.setRefractiveIndex(1.5);
    shape -> setMaterial(newmat);
    Ray r(Tuple::Point(0, 0, sqrt(2)/2), Tuple::Vector(0, 1, 0));
    std::vector<Intersection> xs{Intersection(-sqrt(2)/2, shape), Intersection(sqrt(2)/2, shape)};
    Comps comps(r, xs[1], xs);
    Color c = w.refractedColor(comps, 5);
    REQUIRE(c == Color(0, 0, 0));
}
