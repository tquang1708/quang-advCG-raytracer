/* stripePattern.hpp - implementation of a stripe pattern
 * Quang Tran - 12/4/19
 * */

#pragma once

#include "pattern.hpp"
#include <vector>

class StripePattern : public Pattern{
    private:
        std::vector<Color> stripeColors;
        int colorsNo;

    public:
        StripePattern(std::vector<Color>);
        Color patternAt(Tuple point);
        Color patternAtObject(std::shared_ptr<Object> object, Tuple point);
};
