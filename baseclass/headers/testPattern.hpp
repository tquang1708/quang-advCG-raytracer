/**/

#include "pattern.hpp"

class TestPattern : public Pattern {
    public:
        TestPattern();
        Color patternAt(Tuple);
        Color patternAtObject(std::shared_ptr<Object>, Tuple);
};
