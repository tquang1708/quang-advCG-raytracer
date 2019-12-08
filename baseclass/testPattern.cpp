/* it does what it says it does
 * */

#include "headers/testPattern.hpp"

TestPattern::TestPattern() {
    transform = Matrix::Identity();
}

Color TestPattern::patternAt(Tuple point) {
    return Color(point.getx(), point.gety(), point.getz());
}

Color TestPattern::patternAtObject(std::shared_ptr<Object> object, Tuple point) {
    Tuple objectPoint = object -> getTransform().inverse() * point;
    Tuple patternPoint = transform.inverse() * objectPoint;

    return patternAt(patternPoint);
}
