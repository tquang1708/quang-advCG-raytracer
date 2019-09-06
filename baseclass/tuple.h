/* tuple.h - header file for tuple class
 * used to represent points/vectors
 * Quang Tran - 9/4/2019
 * */

#ifndef TUPLE_H
#define TUPLE_H

class tuple {
    private:
        double x;
        double y;
        double z;
        double w; //w=1 is point, w=0 is vect

    public:
        //named constructor idiom found at
        //https://isocpp.org/wiki/faq/ctors#named-ctor-idiom
        tuple(double x_, double y_, double z_, double w_);

        static tuple point(double x_, double y_, double z_);
        static tuple vector(double x_, double y_, double z_);

        //getter functions
        double getx();
        double gety();
        double getz();
        double getw();

        bool isPoint();
        bool isVector();

        //a lot of help with operator overloading taken from
        //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
        bool operator== (const tuple &a) const;
        tuple operator+(const tuple &a);
        tuple operator-(const tuple &a);
};

#endif
