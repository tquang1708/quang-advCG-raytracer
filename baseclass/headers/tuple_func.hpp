/* tuple_func.h - header file for tuple type functions
 *
 * Quang Tran - 9/6/2019
 * */

#ifndef TUPLE_FUNC_H
#define TUPLE_FUNC_H

#include "tuple.hpp"

double magnitude(tuple a);
tuple normalize(tuple a);
double dot(tuple a, tuple b);
tuple cross(tuple a, tuple b);

#endif
