/* triangle.cpp - implementation of triangle functions
 * Quang Tran - 10/23/19
 * */

#include "headers/triangle.hpp"
#include "headers/baseclass_funcs.hpp"
#include "headers/matrix.hpp"

Triangle::Triangle(Tuple point_a, Tuple point_b, Tuple point_c): point_a(point_a), point_b(point_b), point_c(point_c) {
}

std::vector<double> Triangle::intersect(const Ray r) {
    Matrix denom(3);
    Tuple dir = r.getDirection();
    double denomVal[9] = {point_a.getx() - point_b.getx(), point_a.getx() - point_c.getx(), dir.getx(),
                          point_a.gety() - point_b.gety(), point_a.gety() - point_c.gety(), dir.gety(),
                          point_a.getz() - point_b.getz(), point_a.getz() - point_c.getz(), dir.getz()};
    denom.fillMatrix(denomVal);
    double denomDet = denom.determinant();

    std::vector<double> out;
    //check whether denominator is 0 if yes return empty vector
    if (denomDet == 0) {
        return out;
    }

    //calc B
    Tuple origin = r.getOrigin();
    Matrix numeB(3);
    double numeBVal[9] = {point_a.getx() - origin.getx(), point_a.getx() - point_c.getx(), dir.getx(),
                          point_a.gety() - origin.gety(), point_a.gety() - point_c.gety(), dir.gety(),
                          point_a.getz() - origin.getz(), point_a.getz() - point_c.getz(), dir.getz()};
    numeB.fillMatrix(numeBVal);
    double B = numeB.determinant() / denomDet;

    //calc y
    Matrix numeY(3);
    double numeYVal[9] = {point_a.getx() - point_b.getx(), point_a.getx() - origin.getx(), dir.getx(),
                          point_a.gety() - point_b.gety(), point_a.gety() - origin.gety(), dir.gety(),
                          point_a.getz() - point_b.getz(), point_a.getz() - origin.getz(), dir.getz()};
    numeY.fillMatrix(numeYVal);
    double Y = numeY.determinant() / denomDet;

    //check whether t exists
    if ((B < 0) || (Y < 0) || (B + Y > 1)) {
        return out;
    } else {
        //calc t
        Matrix numeT(3);
        double numeTVal[9] = {point_a.getx() - point_b.getx(), point_a.getx() - point_c.getx(), point_a.getx() - origin.getx(),
                              point_a.gety() - point_b.gety(), point_a.gety() - point_c.gety(), point_a.gety() - origin.gety(),
                              point_a.getz() - point_b.getz(), point_a.getz() - point_c.getz(), point_a.getz() - origin.getz()};
        numeT.fillMatrix(numeTVal);
        double T = numeT.determinant() / denomDet;
        out.push_back(T);
    }

    return out;

}

Tuple Triangle::normalAt(const Tuple point) {
    (void)point;
    return cross(point_a - point_b, point_a - point_c).normalize();
}
