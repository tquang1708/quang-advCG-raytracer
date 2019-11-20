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
    reflectivity = 0.0;
    emission = 0.0;
    transparency = 0.0;
    refractive_index = 1.0;
    shadow_cast = true;
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

double Material::getReflectivity() const {
    return reflectivity;
}

double Material::getEmission() const {
    return emission;
}

double Material::getTransparency() const {
    return transparency;
}

double Material::getRefractiveIndex() const {
    return refractive_index;
}

bool Material::getShadowCast() const {
    return shadow_cast;
}

//setter
Material Material::setColor(Color c) {
    color = c;
    return *this;
}

Material Material::setDiffuse(double d) {
    diffuse = d;
    return *this;
}

Material Material::setAmbient(double a) {
    ambient = a;
    return *this;
}

Material Material::setShininess(double s) {
    shininess = s;
    return *this;
}

Material Material::setSpecular(double s) {
    specular = s;
    return *this;
}

Material Material::setReflectivity(double r) {
    reflectivity = r;
    return *this;
}

Material Material::setEmission(double e) {
    emission = e;
    return *this;
}

Material Material::setTransparency(double t) {
    transparency = t;
    return *this;
}

Material Material::setRefractiveIndex(double ri) {
    refractive_index = ri;
    return *this;
}

Material Material::setShadowCast(bool sc) {
    shadow_cast = sc;
    return *this;
}

//operator overloading
bool Material::operator== (const Material &m) const {
    return((diffuse == m.getDiffuse()) && (color == m.getColor()));
}
