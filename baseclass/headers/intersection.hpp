/* intersection.hpp - storing intersections
 * Quang Tran - 10/9/19
 * */

#pragma once

#include "object.hpp"
#include <memory>

class Intersection {
    private:
        double time;
        std::shared_ptr<Object> object;
    public:
        Intersection();
        Intersection(double t, std::shared_ptr<Object> o);

        //getter funcs
        double getTime() const;
        std::shared_ptr<Object> getObject() const;

        //for use with sort
        bool operator<(const Intersection &i) const;

        //for use with refract
        bool operator==(const Intersection &i) const;
};
