/* intersection.hpp - storing intersections
 * Quang Tran - 10/9/19
 * */

#pragma once

#include "object.hpp"

class Intersection {
    private:
        double time;
        Object* object;
    public:
        Intersection(double t, Object* o);

        //getter funcs
        double getTime() const;
        Object* getObject() const;

        //for use with sort
        bool operator<(const Intersection &i) const;
};
