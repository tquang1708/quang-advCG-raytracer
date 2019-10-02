/* baseclass_funcs.hpp - header file for functions used to work with
 * base classes, or fundamental classes
 * Quang Tran - 9/7/2019
 * */

#ifndef BASECLASS_FUNCS_HPP
#define BASECLASS_FUNCS_HPP

#include "tuple.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "material.hpp"
#include "pointlight.hpp"

double dot(Tuple a, Tuple b);
Tuple cross(Tuple a, Tuple b);
Color lighting(Material m, PointLight light, Tuple hitPoint, Tuple normalv, Tuple camera);

#endif
