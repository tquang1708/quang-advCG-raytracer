/* tuple.h - header file for tuple class
 * used to represent points/vectors
 * Quang Tran - 9/4/2019
 * */

#ifndef TUPLE_H
#define TUPLE_H

const double EPSILON = 0.000001;

class tuple {
    protected:
        double x;
        double y;
        double z;
        double w; //w=1 is point, w=0 is vect

    public:
        //default constructor
        tuple();

        //named constructor idiom found at
        //https://isocpp.org/wiki/faq/ctors#named-ctor-idiom
        tuple(double x_, double y_, double z_, double w_);

        static tuple point(double x_, double y_, double z_);
        static tuple vector(double x_, double y_, double z_);

        //getter functions
        double getx() const;
        double gety() const;
        double getz() const;
        double getw() const;

        bool isPoint();
        bool isVector();

        //a lot of help with operator overloading taken from
        //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
        bool operator== (const tuple &a) const;
        tuple operator+(const tuple &a);
        tuple operator-(const tuple &a);
        tuple operator-();
        tuple& operator=(const tuple &a);
        tuple operator*(const double &scalar);
        tuple operator/(const double &scalar);
};

#endif
