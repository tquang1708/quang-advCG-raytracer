/*arealight header*/

#pragma once

#include "color.hpp"

class AreaLight {
    public:
        Tuple lowCorner;
        Tuple wCorner;
        Tuple hCorner;
        int wSteps;
        int hSteps;

        Color intensity;

        AreaLight(Tuple, Tuple, Tuple, int, int, Color);
};
