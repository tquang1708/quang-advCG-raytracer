/* ray.hpp - header file for class ray
 * Quang Tran - 9/7/2019
 * */

#ifndef RAY_HPP
#define RAY_HPP

#include "tuple.hpp"

class Ray {
    protected:
        Tuple origin;
        Tuple direction;
    public:
        //constructos
        Ray();
        Ray(Tuple origin_, Tuple direction_);

        //getter funcs
        Tuple getOrigin() const;
        Tuple getDirection() const;

        //other funcs
        Tuple position(double time) const;
};

#endif
