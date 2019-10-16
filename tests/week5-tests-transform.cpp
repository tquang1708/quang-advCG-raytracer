#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"

#include <vector>

TEST_CASE("Rotating a point around the x axis") {
    Tuple p = Tuple::Point(0, 1, 0);
    Matrix HalfQuarter = Matrix::Rotation('x', 45);
    Matrix FullQuarter = Matrix::Rotation('x', 90);
    REQUIRE(HalfQuarter * p == Tuple::Point(0, sqrt(2)/2, sqrt(2)/2));
    REQUIRE(FullQuarter * p == Tuple::Point(0, 0, 1));
}

TEST_CASE("The inverse of an x-rotation rotates in the opposite direction") {
    Tuple p = Tuple::Point(0, 1, 0);
    Matrix halfQuarter = Matrix::Rotation('x', 45);
    Matrix inv = halfQuarter.inverse();
    REQUIRE(inv * p == Tuple::Point(0, sqrt(2)/2, -sqrt(2)/2));
}

TEST_CASE("Rotating a point around the y axis") {
    Tuple p = Tuple::Point(0, 0, 1);
    Matrix halfQuarter = Matrix::Rotation('y', 45);
    Matrix fullQuarter = Matrix::Rotation('y', 90);
    REQUIRE(halfQuarter * p == Tuple::Point(sqrt(2)/2, 0, sqrt(2)/2));
    REQUIRE(fullQuarter * p == Tuple::Point(1, 0, 0));
}

TEST_CASE("Rotating a point around the z axis") {
    Tuple p = Tuple::Point(0, 1, 0);
    Matrix halfQuarter = Matrix::Rotation('z', 45);
    Matrix fullQuarter = Matrix::Rotation('z', 90);
    REQUIRE(halfQuarter * p == Tuple::Point(-sqrt(2)/2, sqrt(2)/2, 0));
    REQUIRE(fullQuarter * p == Tuple::Point(-1, 0, 0));
}
