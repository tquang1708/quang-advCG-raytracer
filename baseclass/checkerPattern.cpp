/*checkerPattern.cpp - it does what it does*/

#include "headers/checkerPattern.hpp"

CheckerPattern::CheckerPattern(Color c1, Color c2): color1(c1), color2(c2) {
    transform = Matrix::Identity();
}

Color CheckerPattern::patternAt(Tuple point) {
    if ((int) (floor(point.getx()) + floor(point.gety()) + floor(point.getz())) % 2 == 0.0) {
        return color1;
    } else {
        return color2;
    }
}
