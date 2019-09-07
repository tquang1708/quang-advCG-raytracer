/* tuple_func.h - header file for tuple type functions
 *
 * Quang Tran - 9/6/2019
 * */

#ifndef TUPLE_FUNC_H
#define TUPLE_FUNC_H

#include "tuple.hpp"

double magnitude(Tuple a);
Tuple normalize(Tuple a);
double dot(Tuple a, Tuple b);
Tuple cross(Tuple a, Tuple b);

#endif
