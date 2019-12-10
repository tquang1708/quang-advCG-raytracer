/* light.hpp - header file for light object
 * Quang Tran - 9/14/19
 * */

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "tuple.hpp"
#include "color.hpp"

class PointLight {
    private:
        Tuple position;
        Color intensity;
    public:
        PointLight(Tuple position_, Color intensity_);
        Tuple getPosition() const;
        Color getIntensity() const;
};

#endif
