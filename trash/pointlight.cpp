/* light.cpp - implementation of functions in light.hpp
 * Quang Tran - 9/15/19
 * */

#include "headers/pointlight.hpp"

PointLight::PointLight(Tuple pos, Color intensity): position(pos), intensity(intensity) {
}

Tuple PointLight::getPosition() const {
    return position;
}

Color PointLight::getIntensity() const {
    return intensity;
}
