/* it does what it says it does
 * */

#include "headers/testPattern.hpp"

TestPattern::TestPattern() {
    transform = Matrix::Identity();
}

Color TestPattern::patternAt(Tuple point) {
    return Color(point.getx(), point.gety(), point.getz());
}
