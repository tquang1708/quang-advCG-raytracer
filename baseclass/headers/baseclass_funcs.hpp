/* baseclass_funcs.hpp - header file for functions used to work with
 * base classes, or fundamental classes
 * Quang Tran - 9/7/2019
 * */

#ifndef BASECLASS_FUNCS_HPP
#define BASECLASS_FUNCS_HPP

#include "tuple.hpp"
#include "ray.hpp"

double magnitude(Tuple a);
Tuple normalize(Tuple a);
double dot(Tuple a, Tuple b);
Tuple cross(Tuple a, Tuple b);

Tuple position(Ray r, double time);

#endif
