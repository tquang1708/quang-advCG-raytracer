/* stripePattern.cpp - implementation of a striped pattern
 * Quang Tran - 12/4/19
 * */

#include "headers/stripePattern.hpp"
#include <iostream>

StripePattern::StripePattern(std::vector<Color> colorVector) {
    transform = Matrix::Identity();
    stripeColors = colorVector;
    colorsNo = colorVector.size();
}

Color StripePattern::patternAt(Tuple point) {
    int x = abs(floor(point.getx()));
    return stripeColors[x % colorsNo];
}

Color StripePattern::patternAtObject(std::shared_ptr<Object> object, Tuple point) {
    Tuple objectPoint = object -> getTransform().inverse() * point;
    Tuple patternPoint = transform.inverse() * objectPoint;

    return patternAt(patternPoint);
}
