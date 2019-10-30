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

        //calculate emission
        Color emission = m.getColor() * m.getEmission();

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
        Color out = diffuse + ambient + specular + emission;
        out.clamp();
        return out;
    }
}

//view transformation
Matrix viewTransform(Tuple from, Tuple to, Tuple up) {
    Tuple forward = (to - from).normalize();
    Tuple upn = up.normalize();
    Tuple left = cross(forward, upn);
    Tuple trueUp = cross(left, forward);

    //filling the orientation matrix
    Matrix orientation(4);
    double valArray[16] = {left.getx(), left.gety(), left.getz(), 0,
                           trueUp.getx(), trueUp.gety(), trueUp.getz(), 0,
                           -forward.getx(), -forward.gety(), -forward.getz(), 0,
                           0, 0, 0, 1};
    orientation.fillMatrix(valArray);

    //finally
    return orientation * Matrix::Translation(-from.getx(), -from.gety(), -from.getz());
}
