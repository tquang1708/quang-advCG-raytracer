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

TEST_CASE("refracted color - refracted ray") {
    World w = World::DefaultWorld();
    std::shared_ptr<TestPattern> test = std::make_shared<TestPattern>();
    std::shared_ptr<Sphere> shape = std::dynamic_pointer_cast<Sphere>(w.getObject(0));

    Material newmat = shape -> getMaterial();
    newmat.setAmbient(1.0);
    newmat.setPattern(test);
    shape -> setMaterial(newmat);

    std::shared_ptr<Sphere> shape2 = std::dynamic_pointer_cast<Sphere>(w.getObject(1));
    Material newmat2 = shape2 -> getMaterial();
    newmat2.setTransparency(1.0);
    newmat2.setRefractiveIndex(1.5);
    shape2 -> setMaterial(newmat2);

    Ray r(Tuple::Point(0, 0, 0.1), Tuple::Vector(0, 1, 0));
    std::vector<Intersection> xs{Intersection(-0.9899, shape), Intersection(-0.4899, shape2), Intersection(0.4899, shape2), Intersection(0.9899, shape)};
    Comps comps(r, xs[2], xs);
    Color c = w.refractedColor(comps, 5);

    REQUIRE(c == Color(0, 0.99888, 0.04725));
}

TEST_CASE("shade hit with transparent") {
    World w = World::DefaultWorld();

    std::shared_ptr<Plane> floor = std::make_shared<Plane>();
    floor -> setTransform(Matrix::Translation(0, -1, 0));
    Material floorMat = floor -> getMaterial();
    floorMat.setTransparency(0.5);
    floorMat.setRefractiveIndex(1.5);
    floor -> setMaterial(floorMat);
    w.addObject(floor);

    std::shared_ptr<Sphere> ball = std::make_shared<Sphere>();
    ball -> setTransform(Matrix::Translation(0, -3.5, -0.5));
    Material ballMat = ball -> getMaterial();
    ballMat.setColor(Color(1, 0, 0));
    ballMat.setAmbient(0.5);
    ball -> setMaterial(ballMat);
    w.addObject(ball);

    Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, -sqrt(2)/2, sqrt(2)/2));
    std::vector<Intersection> xs{Intersection(sqrt(2), floor)};
    Comps comps(r, xs[0], xs);
    Color color = w.shadeHit(comps, 5);
    REQUIRE (color == Color(0.93642, 0.68642, 0.68642));
}

TEST_CASE("schlick - tir") {
    std::shared_ptr<Sphere> glass = std::make_shared<Sphere>(Sphere::GlassSphere());
    Ray r(Tuple::Point(0, 0, sqrt(2) / 2), Tuple::Vector(0, 1, 0));
    std::vector<Intersection> xs{Intersection(-sqrt(2)/2, glass), Intersection(sqrt(2)/2, glass)};
    Comps comps(r, xs[1], xs);
    double reflectance = comps.schlick();
    REQUIRE(reflectance == 1.0);
}

TEST_CASE("perpendicular ray") {
    std::shared_ptr<Sphere> glass = std::make_shared<Sphere>(Sphere::GlassSphere());
    Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 1, 0));
    std::vector<Intersection> xs{Intersection(-1, glass), Intersection(1, glass)};
    Comps comps(r, xs[1], xs);
    double reflectance = comps.schlick();
    REQUIRE(reflectance == 0.04);
}

TEST_CASE("n2 > n1") {
    std::shared_ptr<Sphere> glass = std::make_shared<Sphere>(Sphere::GlassSphere());
    Ray r(Tuple::Point(0, 0.99, -2), Tuple::Vector(0, 0, 1));
    std::vector<Intersection> xs{Intersection(1.8589, glass)};
    Comps comps(r, xs[0], xs);
    double reflectance = comps.schlick();
    REQUIRE(reflectance == 0.48873);
}

TEST_CASE("reflectance reflection refraction") {
    World w = World::DefaultWorld();
    Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, -sqrt(2)/2, sqrt(2)/2));

    std::shared_ptr<Plane> floor = std::make_shared<Plane>();
    floor -> setTransform(Matrix::Translation(0, -1, 0));
    Material mf;
    mf.setReflectivity(0.5);
    mf.setTransparency(0.5);
    mf.setRefractiveIndex(1.5);
    floor -> setMaterial(mf);
    w.addObject(floor);

    std::shared_ptr<Sphere> ball = std::make_shared<Sphere>();
    ball -> setTransform(Matrix::Translation(0, -3.5, -0.5));
    Material mb;
    mb.setColor(Color(1, 0, 0));
    mb.setAmbient(0.5);
    ball -> setMaterial(mb);
    w.addObject(ball);

    std::vector<Intersection> xs{Intersection(sqrt(2), floor)};
    Comps comps(r, xs[0], xs);
    Color c = w.shadeHit(comps, 5);
    REQUIRE(c == Color(0.93391, 0.69643, 0.69243));
}
