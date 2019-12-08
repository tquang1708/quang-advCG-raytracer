/*checkerPattern.hpp - it does what it does*/

#pragma once

#include "pattern.hpp"

class CheckerPattern : public Pattern {
    private:
        Color color1;
        Color color2;

    public:
        CheckerPattern(Color, Color);
        Color patternAt(Tuple point);
};
