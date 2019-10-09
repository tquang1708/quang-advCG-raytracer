/* material.cpp - Implementation of funcs in material.hpp
 * Quang Tran - 9/15/19
 * */

#include "headers/material.hpp"

Material::Material() {
    color = Color(1, 1, 1);
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200;
}

Color Material::getColor() const {
    return color;
}

//getter
double Material::getDiffuse() const {
    return diffuse;
}

double Material::getAmbient() const {
    return ambient;
}

double Material::getShininess() const {
    return shininess;
}

double Material::getSpecular() const {
    return specular;
}

//setter
void Material::setColor(Color c) {
    color = c;
}

void Material::setDiffuse(double d) {
    diffuse = d;
}

void Material::setAmbient(double a) {
    ambient = a;
}

void Material::setShininess(double s) {
    shininess = s;
}

void Material::setSpecular(double s) {
    specular = s;
}

//operator overloading
bool Material::operator== (const Material &m) const {
    return((diffuse == m.getDiffuse()) && (color == m.getColor()));
}
