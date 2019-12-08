/* patterns.hpp - header file for pattern abstract class
 * Quang Tran - 4/12/19
 * */

#pragma once

#include "color.hpp"
#include "tuple.hpp"
#include "matrix.hpp"
#include "object.hpp"

#include <memory>

class Pattern {
    protected:
        Matrix transform;
    public:
        Pattern();

        //getter
        Matrix getTransform() const;

        //setter
        void setTransform(Matrix);

        //pure virtual func
        virtual Color patternAt(Tuple point) = 0;
        virtual Color patternAtObject(std::shared_ptr<Object> object, Tuple point) = 0;
};