/*implementation*/

#include "headers/arealight.hpp"

AreaLight::AreaLight(Tuple c, Tuple a1, Tuple a2, int s1, int s2, Color i):
    lowCorner(c), wCorner(a1), hCorner(a2), wSteps(s1), hSteps(s2), intensity(i) {}
