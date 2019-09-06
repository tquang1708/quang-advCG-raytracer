#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"
#include "math.h"

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

TEST_CASE("Negating a tuple") {
    tuple a(1, -2, 3, -4);
    tuple a_ng(-1, 2, -3, 4);
    REQUIRE (-a == a_ng);
}

TEST_CASE("Bonus: Assignment") {
    tuple a(1, 2, 3, 4);
    tuple a1(2, 3, 4, 5);
    a = a1;
    REQUIRE (a == a1);
}

TEST_CASE("Multiplying a tuple by a scalar") {
    tuple a(1, -2, 3, -4);
    tuple res(3.5, -7, 10.5, -14);
    REQUIRE(a * 3.5 == res);
}

TEST_CASE("Multiplying a tuple by a fraction") {
    tuple a(1, -2, 3, -4);
    tuple res(0.5, -1, 1.5, -2);
    REQUIRE(a * 0.5 == res);
}

TEST_CASE("Dividing a tuple by a scalar") {
    tuple a(1, -2, 3, -4);
    tuple res(0.5, -1, 1.5, -2);
    REQUIRE(a / 2 == res);
}

TEST_CASE("Computing the magnitude of vector(1, 0 ,0)") {
    tuple v = tuple::vector(1, 0, 0);
    REQUIRE(magnitude(v) == 1);
}

TEST_CASE("Computing the magnitude of vector(0, 1 ,0)") {
    tuple v = tuple::vector(0, 1, 0);
    REQUIRE(magnitude(v) == 1);
}

TEST_CASE("Computing the magnitude of vector(0, 0 ,1)") {
    tuple v = tuple::vector(0, 0, 1);
    REQUIRE(magnitude(v) == 1);
}

TEST_CASE("Computing the magnitude of vector(1, 2 ,3)") {
    tuple v = tuple::vector(1, 2, 3);
    REQUIRE(magnitude(v) == sqrt(14));
}

TEST_CASE("Computing the magnitude of vector(-1, -2, -3)") {
    tuple v = tuple::vector(-1, -2, -3);
    REQUIRE(magnitude(v) == sqrt(14));
}

TEST_CASE("Normalizing vector (4, 0, 0) gives (1, 0, 0)") {
    tuple v = tuple::vector(4, 0, 0);
    tuple res = tuple::vector(1, 0, 0);
    REQUIRE(normalize(v) == res);
}

TEST_CASE("Normalizing vector (1, 2, 3)") {
    tuple v = tuple::vector(1, 2, 3);
    tuple res = tuple::vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14));
    REQUIRE(normalize(v) == res);
}

TEST_CASE("The magnitude of a normalized vector") {
    tuple v = tuple::vector(1, 2, 3);
    tuple norm = normalize(v);
    REQUIRE(magnitude(norm) == 1);
}

TEST_CASE("The dot product of two tuples") {
    tuple a = tuple::vector(1, 2, 3);
    tuple b = tuple::vector(2, 3, 4);
    REQUIRE(dot(a, b) == 20);
}

TEST_CASE("The cross product of two tuples") {
    tuple a = tuple::vector(1, 2, 3);
    tuple b = tuple::vector(2, 3, 4);
    tuple crossab = tuple::vector(-1, 2, -1);
    tuple crossba = tuple::vector(1, -2, 1);
    REQUIRE(cross(a, b) == crossab);
    REQUIRE(cross(b, a) == crossba);
}

TEST_CASE("Colors are (red, green, blue) tuples") {
    color a(-0.5, 0.4, 1.7);
    REQUIRE(a.getR() == -0.5);
    REQUIRE(a.getG() == 0.4);
    REQUIRE(a.getB() == 1.7);
}

TEST_CASE("Adding colors") {
    color c1(0.9, 0.6, 0.75);
    color c2(0.7, 0.1, 0.25);
    REQUIRE(c1 + c2 == color(1.6, 0.7, 1.0));
}

TEST_CASE("Subtracting colors") {
    color c1(0.9, 0.6, 0.75);
    color c2(0.7, 0.1, 0.25);
    REQUIRE(c1 - c2 == color(0.2, 0.5, 0.5));
}

TEST_CASE("Multiplying a color by a scalar") {
    color c(0.2, 0.3, 0.4);
    REQUIRE(c * 2 == color(0.4, 0.6, 0.8));
}

TEST_CASE("Multiplying colors") {
    color c1(1, 0.2, 0.4);
    color c2(0.9, 1, 0.1);
    REQUIRE(c1 * c2 == color(0.9, 0.2, 0.04));
}
