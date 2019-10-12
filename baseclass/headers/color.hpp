/* color.h - header file for color class, which is a child of tuple
 * RGB color, value from 0 to 1
 * Quang Tran - 9/6/2019
 * */

#ifndef COLOR_H
#define COLOR_H

#include "tuple.hpp"

class Color : public Tuple {
    public:
        Color();
        Color(double red_, double green_, double blue_);

        //getter function
        double getR() const;
        double getG() const;
        double getB() const;

        //setter funcs
        void setR(const double newR);
        void setG(const double newR);
        void setB(const double newR);

        //special operator overloading for color
        Color operator*(const double &scalar) const;
        Color operator*(const Color &a) const;
        Color operator+(const Color &a) const;
        Color& operator=(const Color &a);

        //color clamping
        void clamp();
};

#endif
