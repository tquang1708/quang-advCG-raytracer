/* light.cpp - implementation of functions in light.hpp
 * Quang Tran - 9/15/19
 * */

#include "headers/pointlight.hpp"

PointLight::PointLight(Tuple position_, Color intensity_) {
    position = position_;
    intensity = intensity_;
}

Tuple PointLight::getPosition() const {
    return position;
}

Color PointLight::getIntensity() const {
    return intensity;
}
