/* material.cpp - Implementation of funcs in material.hpp
 * Quang Tran - 9/15/19
 * */

#include "headers/material.hpp"

Material::Material() {
    color = Color(1, 1, 1);
    ambient = 0.2;
    diffuse = 1.0;
    shininess = 0.8;
    emission = 0.0;
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

double Material::getEmission() const {
    return emission;
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

void Material::setEmission(double e) {
    emission = e;
}

//operator overloading
bool Material::operator== (const Material &m) const {
    return((diffuse == m.getDiffuse()) && (color == m.getColor()));
}
