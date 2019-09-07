#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"
#include "math.h"

TEST_CASE("A Tuple with w=1.0 is a Point") {
    Tuple a(4.3, -4.2, 3.1, 1.0);

    REQUIRE(a.getx() == 4.3);
    REQUIRE(a.gety() == -4.2);
    REQUIRE(a.getz() == 3.1);
    REQUIRE(a.getw() == 1.0);
    REQUIRE(a.isPoint() == true);
    REQUIRE(a.isVector() == false);
}

TEST_CASE("A Tuple with w=0 is a Vector") {
    Tuple a(4.3, -4.2, 3.1, 0.0);

    REQUIRE (a.getx() == 4.3);
    REQUIRE (a.gety() == -4.2);
    REQUIRE (a.getz() == 3.1);
    REQUIRE (a.getw() == 0.0);
    REQUIRE(a.isPoint() == false);
    REQUIRE(a.isVector() == true);
}

TEST_CASE("Point() creates Tuples with w=1") {
    Tuple p = Tuple::Point(4, -4, 3);
    Tuple a(4, -4, 3, 1);
    REQUIRE (a == p);
}

TEST_CASE("Vector() creates Tuples with w=0") {
    Tuple v = Tuple::Vector(4, -4, 3);
    Tuple a(4, -4, 3, 0);
    REQUIRE (a == v);
}

TEST_CASE("Adding two Tuples") {
    Tuple a1(3, -2, 5, 1);
    Tuple a2(-2, 3, 1, 0);
    REQUIRE (a1 + a2 == Tuple(1, 1, 6, 1));
}

TEST_CASE("Subtracting two Points") {
    Tuple p1 = Tuple::Point(3, 2, 1);
    Tuple p2 = Tuple::Point(5, 6, 7);
    REQUIRE (p1 - p2 == Tuple::Vector(-2, -4, -6));
}

TEST_CASE("Subtracting a Vector from a Point") {
    Tuple p = Tuple::Point(3, 2, 1);
    Tuple v = Tuple::Vector(5, 6, 7);
    REQUIRE (p - v == Tuple::Point(-2, -4, -6));
}

TEST_CASE("Subtracting two Vectors") {
    Tuple v1 = Tuple::Vector(3, 2, 1);
    Tuple v2 = Tuple::Vector(5, 6, 7);
    REQUIRE (v1 - v2 == Tuple::Vector(-2, -4, -6));
}

TEST_CASE("Subtracting a Vector from the zero Vector") {
    Tuple zero = Tuple::Vector(0, 0, 0);
    Tuple v = Tuple::Vector(1, -2, 3);
    REQUIRE (zero - v == Tuple::Vector(-1, 2, -3));
}

TEST_CASE("Negating a Tuple") {
    Tuple a(1, -2, 3, -4);
    Tuple a_ng(-1, 2, -3, 4);
    REQUIRE (-a == a_ng);
}

TEST_CASE("Bonus: Assignment") {
    Tuple a(1, 2, 3, 4);
    Tuple a1(2, 3, 4, 5);
    a = a1;
    REQUIRE (a == a1);
}

TEST_CASE("Multiplying a Tuple by a scalar") {
    Tuple a(1, -2, 3, -4);
    Tuple res(3.5, -7, 10.5, -14);
    REQUIRE(a * 3.5 == res);
}

TEST_CASE("Multiplying a Tuple by a fraction") {
    Tuple a(1, -2, 3, -4);
    Tuple res(0.5, -1, 1.5, -2);
    REQUIRE(a * 0.5 == res);
}

TEST_CASE("Dividing a Tuple by a scalar") {
    Tuple a(1, -2, 3, -4);
    Tuple res(0.5, -1, 1.5, -2);
    REQUIRE(a / 2 == res);
}

TEST_CASE("Computing the magnitude of Vector(1, 0 ,0)") {
    Tuple v = Tuple::Vector(1, 0, 0);
    REQUIRE(v.magnitude() == 1);
}

TEST_CASE("Computing the magnitude of Vector(0, 1 ,0)") {
    Tuple v = Tuple::Vector(0, 1, 0);
    REQUIRE(v.magnitude() == 1);
}

TEST_CASE("Computing the magnitude of Vector(0, 0 ,1)") {
    Tuple v = Tuple::Vector(0, 0, 1);
    REQUIRE(v.magnitude() == 1);
}

TEST_CASE("Computing the magnitude of Vector(1, 2 ,3)") {
    Tuple v = Tuple::Vector(1, 2, 3);
    REQUIRE(v.magnitude() == sqrt(14));
}

TEST_CASE("Computing the magnitude of Vector(-1, -2, -3)") {
    Tuple v = Tuple::Vector(-1, -2, -3);
    REQUIRE(v.magnitude() == sqrt(14));
}

TEST_CASE("Normalizing Vector (4, 0, 0) gives (1, 0, 0)") {
    Tuple v = Tuple::Vector(4, 0, 0);
    Tuple res = Tuple::Vector(1, 0, 0);
    REQUIRE(v.normalize() == res);
}

TEST_CASE("Normalizing Vector (1, 2, 3)") {
    Tuple v = Tuple::Vector(1, 2, 3);
    Tuple res = Tuple::Vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14));
    REQUIRE(v.normalize() == res);
}

TEST_CASE("The magnitude of a normalized Vector") {
    Tuple v = Tuple::Vector(1, 2, 3);
    Tuple norm = v.normalize();
    REQUIRE(norm.magnitude() == 1);
}

TEST_CASE("The dot product of two Tuples") {
    Tuple a = Tuple::Vector(1, 2, 3);
    Tuple b = Tuple::Vector(2, 3, 4);
    REQUIRE(dot(a, b) == 20);
}

TEST_CASE("The cross product of two Tuples") {
    Tuple a = Tuple::Vector(1, 2, 3);
    Tuple b = Tuple::Vector(2, 3, 4);
    Tuple crossab = Tuple::Vector(-1, 2, -1);
    Tuple crossba = Tuple::Vector(1, -2, 1);
    REQUIRE(cross(a, b) == crossab);
    REQUIRE(cross(b, a) == crossba);
}

TEST_CASE("Colors are (red, green, blue) Tuples") {
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

TEST_CASE("Creating and querying a ray") {
    Tuple origin = Tuple::Point(1, 2, 3);
    Tuple direction = Tuple::Vector(4, 5, 6);
    Ray r(origin, direction);
    REQUIRE(r.getOrigin() == origin);
    REQUIRE(r.getDirection() == direction);
}

TEST_CASE("Computing a point from a distance") {
    Ray r(Tuple::Point(2, 3, 4), Tuple::Vector(1, 0, 0));
    REQUIRE(r.position(0) == Tuple::Point(2, 3, 4));
    REQUIRE(r.position(1) == Tuple::Point(3, 3, 4));
    REQUIRE(r.position(-1) == Tuple::Point(1, 3, 4));
    REQUIRE(r.position(2.5) == Tuple::Point(4.5, 3, 4));
}
