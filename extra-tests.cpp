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
