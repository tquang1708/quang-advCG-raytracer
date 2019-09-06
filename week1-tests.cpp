#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/tuple.h"

TEST_CASE("A tuple with w=1.0 is a point") {
    tuple a(4.3, -4.2, 3.1, 1.0);

    REQUIRE(a.getx() == 4.3);
    REQUIRE(a.gety() == -4.2);
    REQUIRE(a.getz() == 3.1);
    REQUIRE(a.getw() == 1.0);
    REQUIRE(a.isPoint() == true);
    REQUIRE(a.isVector() == false);
}

TEST_CASE("A tuple with w=0 is a vector") {
    tuple a(4.3, -4.2, 3.1, 0.0);

    REQUIRE (a.getx() == 4.3);
    REQUIRE (a.gety() == -4.2);
    REQUIRE (a.getz() == 3.1);
    REQUIRE (a.getw() == 0.0);
    REQUIRE(a.isPoint() == false);
    REQUIRE(a.isVector() == true);
}

TEST_CASE("point() creates tuples with w=1") {
    tuple p = tuple::point(4, -4, 3);
    tuple a(4, -4, 3, 1);
    REQUIRE (a == p);
}

TEST_CASE("vector() creates tuples with w=0") {
    tuple v = tuple::vector(4, -4, 3);
    tuple a(4, -4, 3, 0);
    REQUIRE (a == v);
}

TEST_CASE("Adding two tuples") {
    tuple a1(3, -2, 5, 1);
    tuple a2(-2, 3, 1, 0);
    REQUIRE (a1 + a2 == tuple(1, 1, 6, 1));
}

TEST_CASE("Subtracting two points") {
    tuple p1 = tuple::point(3, 2, 1);
    tuple p2 = tuple::point(5, 6, 7);
    REQUIRE (p1 - p2 == tuple::vector(-2, -4, -6));
}

TEST_CASE("Subtracting a vector from a point") {
    tuple p = tuple::point(3, 2, 1);
    tuple v = tuple::vector(5, 6, 7);
    REQUIRE (p - v == tuple::point(-2, -4, -6));
}

TEST_CASE("Subtracting two vectors") {
    tuple v1 = tuple::vector(3, 2, 1);
    tuple v2 = tuple::vector(5, 6, 7);
    REQUIRE (v1 - v2 == tuple::vector(-2, -4, -6));
}

TEST_CASE("Subtracting a vector from the zero vector") {
    tuple zero = tuple::vector(0, 0, 0);
    tuple v = tuple::vector(1, -2, 3);
    REQUIRE (zero - v == tuple::vector(-1, 2, -3));
}
