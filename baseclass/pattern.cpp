/* pattern.cpp - implementation of pattern class
 * */
#include "headers/pattern.hpp"

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
