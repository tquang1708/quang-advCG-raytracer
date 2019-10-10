/* tuple.h - header file for tuple class
 * used to represent points/vectors
 * Quang Tran - 9/4/2019
 * */

#ifndef TUPLE_H
#define TUPLE_H

const double EPSILON = 0.000001;

class Tuple {
    protected:
        double x;
        double y;
        double z;
        double w; //w=1 is point, w=0 is vect

    public:
        //default constructor
        Tuple();

        //named constructor idiom found at
        //https://isocpp.org/wiki/faq/ctors#named-ctor-idiom
        Tuple(double x_, double y_, double z_, double w_);

        static Tuple Point(double x_, double y_, double z_);
        static Tuple Vector(double x_, double y_, double z_);

        //getter functions
        double getx() const;
        double gety() const;
        double getz() const;
        double getw() const;

        void setw(double neww);

        bool isPoint();
        bool isVector();

        //a lot of help with operator overloading taken from
        //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
        bool operator== (const Tuple &a) const;
        bool operator!= (const Tuple &a) const;
        Tuple operator+(const Tuple &a) const;
        Tuple operator-(const Tuple &a) const;
        Tuple operator-() const;
        Tuple& operator=(const Tuple &a);
        Tuple operator*(const double &scalar) const;
        Tuple operator/(const double &scalar) const;

        //other functions
        double magnitude() const;
        Tuple normalize() const;
};

//point
//inline vectors since it is a small function that is called a lot
//constructor and all
inline Tuple Tuple::Point(double x_, double y_, double z_) {
    return Tuple(x_, y_, z_, 1.0);
}

//vector
inline Tuple Tuple::Vector(double x_, double y_, double z_) {
    return Tuple(x_, y_, z_, 0.0);
}

#endif
