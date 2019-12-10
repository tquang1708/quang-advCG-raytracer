/* pattern.cpp - implementation of pattern class
 * */
#include "headers/pattern.hpp"
#include "headers/object.hpp"

//constructor
Pattern::Pattern() {
    transform = Matrix::Identity();
}

//getter
Matrix Pattern::getTransform() const {
    return transform;
}

//setter
void Pattern::setTransform(Matrix t) {
    transform = t;
}

Color Pattern::patternAtObject(std::shared_ptr<Object> object, Tuple point) {
    Tuple objectPoint = object -> getTransform().inverse() * point;
    Tuple patternPoint = transform.inverse() * objectPoint;

    return patternAt(patternPoint);
}
