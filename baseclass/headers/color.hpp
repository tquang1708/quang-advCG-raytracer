/* color.h - header file for color class, which is a child of tuple
 * RGB color, value from 0 to 1
 * Quang Tran - 9/6/2019
 * */

#ifndef COLOR_H
#define COLOR_H

#include "tuple.hpp"

class color : public Tuple {
    public:
        color();
        color(double red_, double green_, double blue_);

        //getter function
        double getR() const;
        double getG() const;
        double getB() const;

        //special operator overloading for color
        color operator*(const double &scalar);
        color operator*(const color &a);
};

#endif
