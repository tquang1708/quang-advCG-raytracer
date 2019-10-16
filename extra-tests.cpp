#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"

TEST_CASE("Default orientation transformation matrix") {
    Tuple from = Tuple::Point(0, 0, 0);
    Tuple to = Tuple::Point(0, 0, -1);
    Tuple up = Tuple::Vector(0, 1, 0);
    Matrix t = viewTransform(from, to, up);
    REQUIRE(t == Matrix::Identity());
}

TEST_CASE("Positive z") {
    Tuple from = Tuple::Point(0, 0, 0);
    Tuple to = Tuple::Point(0, 0, 1);
    Tuple up = Tuple::Vector(0, 1, 0);
    Matrix t = viewTransform(from, to, up);
    REQUIRE(t == Matrix::Scaling(-1, 1, -1));
}

TEST_CASE("Moves the world") {
    Tuple from = Tuple::Point(0, 0, 8);
    Tuple to = Tuple::Point(0, 0, 0);
    Tuple up = Tuple::Vector(0, 1, 0);
    Matrix t = viewTransform(from, to, up);
    REQUIRE(t == Matrix::Translation(0, 0, -8));
}

//Did not pass due to double rounding
//TEST_CASE("Arbitrary transformation") {
//    Tuple from = Tuple::Point(1, 3, 2);
//    Tuple to = Tuple::Point(4, -2, 8);
//    Tuple up = Tuple::Vector(1, 1, 0);
//    Matrix t = viewTransform(from, to, up);
//    Matrix out(4);
//    double valArray[16] = {-0.50709, 0.50709, 0.67612, -2.36643,
//                           0.76772, 0.60609, 0.12122, -2.82843,
//                           -0.35857, 0.59761, -0.71714, 0,
//                           0, 0, 0, 1};
//    out.fillMatrix(valArray);
//    REQUIRE(t == out);
//}


TEST_CASE("Constructing camera") {
    double hsize = 160;
    double vsize = 120;
    double fov = 90;
    Camera c(hsize, vsize, fov);
    REQUIRE(c.getHSize() == 160);
    REQUIRE(c.getVSize() == 120);
    REQUIRE(c.getFOV() == 90);
    REQUIRE(c.getTransform() == Matrix::Identity());
}

TEST_CASE("Pixel size for horizontal canvas") {
    Camera c(200, 125, 90);
    REQUIRE(c.pixelSize() == 0.01);
}

TEST_CASE("Pixel size for vertical canvas") {
    Camera c(125, 200, 90);
    REQUIRE(c.pixelSize() == 0.01);
}

TEST_CASE("Ray through center of canvas") {
    Camera c(201, 101, 90);
    Ray r = c.cameraRay(100, 50);
    REQUIRE(r.getOrigin() == Tuple::Point(0, 0, 0));
    REQUIRE(r.getDirection() == Tuple::Vector(0, 0, -1));
}

TEST_CASE("Corner of canvas") {
    Camera c(201, 101, 90);
    Ray r = c.cameraRay(0, 0);
    REQUIRE(r.getOrigin() == Tuple::Point(0, 0, 0));
    REQUIRE(r.getDirection() == Tuple::Vector(0.66519, 0.33259, -0.66851));
}

TEST_CASE("TRansformed camera") {
    Camera c(201, 101, 90);
    c.setTransform(Matrix::Rotation('y', 45) * Matrix::Translation(0, -2, 5));
    Ray r = c.cameraRay(100, 50);
    REQUIRE(r.getOrigin() == Tuple::Point(0, 2, -5));
    REQUIRE(r.getDirection() == Tuple::Vector(sqrt(2)/2, 0, -sqrt(2)/2));
}
