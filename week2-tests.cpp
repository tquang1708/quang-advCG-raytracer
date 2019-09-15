#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"
#include <math.h>

TEST_CASE("The normal on a sphere at a point on the x axis") {
    Sphere s;
    Tuple p = Tuple::Point(1, 0, 0);
    Tuple n = s.normalAt(p);
    Tuple test = Tuple::Vector(1, 0, 0);
    REQUIRE(n == test);
}

TEST_CASE("The normal on a sphere at a point on the y axis") {
    Sphere s;
    Tuple p = Tuple::Point(0, 1, 0);
    Tuple n = s.normalAt(p);
    Tuple test = Tuple::Vector(0, 1, 0);
    REQUIRE(n == test);
}

TEST_CASE("The normal on a sphere at a point on the z axis") {
    Sphere s;
    Tuple p = Tuple::Point(0, 0, 1);
    Tuple n = s.normalAt(p);
    Tuple test = Tuple::Vector(0, 0, 1);
    REQUIRE(n == test);
}

TEST_CASE("The normal on a sphere at a nonaxial point") {
    Sphere s;
    Tuple p = Tuple::Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3);
    Tuple n = s.normalAt(p);
    Tuple test = Tuple::Vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3);
    REQUIRE(n == test);
}

TEST_CASE("The normal is a normalized vector") {
    Sphere s;
    Tuple p = Tuple::Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3);
    Tuple n = s.normalAt(p);
    REQUIRE(n == n.normalize());
}

TEST_CASE("A sphere may be assigned a material") {
    Sphere s;
    Material m;
    Color c(0, 0, 1);
    m.setColor(c);
    s.setMaterial(m);
    REQUIRE(s.getMaterial() == m);
}

TEST_CASE("A point light has a position and intensity") {
    Color intensity(1, 1, 1);
    Tuple position = Tuple::Point(0, 0, 0);
    PointLight light(position, intensity);
    REQUIRE(light.getPosition() == position);
    REQUIRE(light.getIntensity() == intensity);
}

TEST_CASE("Feature: Materials") {
    Material m;
    Tuple position = Tuple::Point(0, 0, 0);
    Tuple normalv = Tuple::Vector(0, 0, -1);

    SECTION("The default material") {
        REQUIRE(m.getColor() == Color(1, 1, 1));
        REQUIRE(m.getDiffuse() == 1);
    }

    SECTION("Lighting with the eye between the light and the surface") {
        PointLight light(Tuple::Point(0, 0, -10), Color(1, 1, 1));
        Color result = lighting(m, light, position, normalv);
        REQUIRE(result == Color(1, 1, 1));
    }

    SECTION("Lighting with the eye opposite surface, light offset 45 deg") {
        PointLight light(Tuple::Point(0, 10, -10), Color(1, 1, 1));
        Color result = lighting(m, light, position, normalv);
        REQUIRE(result == Color(0.7364, 0.7364, 0.7364));
    }

    SECTION("Lighting with the light behind the surface") {
        PointLight light(Tuple::Point(0, 0, 10), Color(1, 1, 1));
        Color result = lighting(m, light, position, normalv);
        REQUIRE(result == Color(0, 0, 0));
    }
}
