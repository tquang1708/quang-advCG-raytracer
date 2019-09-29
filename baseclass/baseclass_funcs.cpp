/* baseclass_funcs.cpp - functions that interacts with classes
 * in the baseclass folder
 * Quang Tran - 9/7/2019
 * */

#include "baseclass_headers.hpp"
#include "math.h"
#include <iostream>

//dot product of two vectors
double dot(Tuple a, Tuple b){
    return (a.getx() * b.getx() +
            a.gety() * b.gety() +
a.getz() * b.getz() +
            a.getw() * b.getw());
}

//cross product of two vectors
Tuple cross(Tuple a, Tuple b){
    Tuple out = Tuple::Vector(a.gety() * b.getz() - a.getz() * b.gety(),
                              a.getz() * b.getx() - a.getx() * b.getz(),
                              a.getx() * b.gety() - a.gety() * b.getx());
    return out;
}

//lighting objects
Color lighting(Material m, PointLight light, Tuple hitPoint, Tuple normalv) {
    //calculate diffuse
    Tuple unitVectorToLight = (light.getPosition() - hitPoint).normalize();
    double lightIntensity = dot(normalv, unitVectorToLight);
    Color diffuse = m.getColor() * light.getIntensity() * lightIntensity * m.getDiffuse();

    //calculate ambient
    Color ambient = m.getColor() * light.getIntensity() * m.getAmbient();

    //calculate emission
    Color emission = m.getColor() * m.getEmission();

    //calculate specular
    //Tuple reflectionVector = (normalv * lightIntensity * 2- unitVectorToLight).normalize();
    //double specularIntensity = dot(reflectionVector, unitVectorToLight);
    //Color specular = m.getColor() * specularIntensity;

    //final color
    Color out = diffuse + ambient + emission;
    if (out.getR() < 0) {
        out.setR(0);
    }
    if (out.getG() < 0) {
        out.setG(0);
    }
    if (out.getB() < 0) {
        out.setB(0);
    }
    return out;
}
