/* object.cpp - implementation of declared funcs in object header
 * Quang Tran - 10/9/19
 * */

#include "headers/object.hpp"

Object::Object() {
    material = Material();
    transform = Matrix::Identity();
}

//getter
Material Object::getMaterial() const {
    return material;
}

Matrix Object::getTransform() const {
    return transform;
}

//setter
void Object::setMaterial(Material m) {
    material = m;
}

void Object::setTransform(Matrix t) {
    transform = t;
}
