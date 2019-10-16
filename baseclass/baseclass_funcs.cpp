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
Color lighting(Material m, PointLight light, Tuple hitPoint, Tuple normalv, Tuple eye, bool isShadowed) {
    //calculate ambient
    Color ambient = m.getColor() * light.getIntensity() * m.getAmbient();
   
    //if shadowed return ambient
    if (isShadowed) {
        return ambient;
    } 
    else {
        //calculate diffuse
        Tuple unitVectorToLight = (light.getPosition() - hitPoint).normalize();
        double lightIntensity = dot(normalv, unitVectorToLight);

        //black default case
        Color diffuse(0, 0, 0);
        Color specular(0, 0, 0);
        if (lightIntensity > 0) {
            //calc diffuse if lightInt > 0
            diffuse = m.getColor() * light.getIntensity() * lightIntensity * m.getDiffuse();

            //calculate specular
            Tuple reflectionVector = (normalv * lightIntensity * 2- unitVectorToLight).normalize();
            Tuple unitVectorToEye = (eye - hitPoint).normalize();
            double reflectDotEye = dot(reflectionVector, unitVectorToEye);
            if (reflectDotEye > 0) {
                double specularIntensity = pow(reflectDotEye, m.getShininess());
                specular = light.getIntensity() * specularIntensity * m.getSpecular();
            }
        }

        //final color
        Color out = diffuse + ambient + specular;
        out.clamp();
        return out;
    }
}
