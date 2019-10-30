/* mainPerspWorld.cpp - Main of program with mult obj support
 * Quang Tran - 10/14/2019
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>

int main(int argc, char** argv) {
    //handling inputs for testing
    std::vector<double> a;
    for (int i = 1; i < argc; i++) {
        a.push_back(atof(argv[i]));
    }

    //floor
    Plane floor;
    Material mf;
    mf.setColor(Color(1, 0.9, 0.9));
    mf.setSpecular(0);
    floor.setMaterial(mf);

    //a triangle
    Triangle triangle(Tuple::Point(1, 0, 0),
                      Tuple::Point(0, 3, 4),
                      Tuple::Point(2, 0, 3));
    Material t;
    t.setColor(Color(0, 1, 0));
    triangle.setMaterial(t);

    //mid sphere
    Sphere middle;
    middle.setTransform(Matrix::Translation(-0.5, 1, 0.5));
    Material ms;
    ms.setColor(Color(0.1, 1, 0.5));
    ms.setDiffuse(0.7);
    ms.setSpecular(0.3);
    middle.setMaterial(ms);

    //right sphere
    //lengthen var names
    Sphere right;
    right.setTransform(Matrix::Translation(1.5, 0.5, -0.5) * Matrix::Scaling(0.5, 0.5, 0.5));
    Material mr;
    mr.setColor(Color(0.5, 1, 0.1));
    mr.setDiffuse(0.7);
    mr.setSpecular(0.3);
    right.setMaterial(mr);

    //left sphere
    Sphere left;
    left.setTransform(Matrix::Translation(-1.5, 0.33, -0.75) * Matrix::Scaling(0.33, 0.33, 0.33));
    Material ml;
    ml.setColor(Color(1, 0.8, 0.1));
    ml.setDiffuse(0.7);
    ml.setSpecular(0.3);
    left.setMaterial(ml);

    //point light
    PointLight pl1(Tuple::Point(-10, 10, -10), Color(1, 1, 1));
    PointLight pl2(Tuple::Point(0, 10, 10), Color(0, 1, 0));
    PointLight pl3(Tuple::Point(10, 10, -10), Color(0, 0, 1));

    //world
    World w;
    w.addLight(&pl1);
    //w.addLight(&pl2);
    //w.addLight(&pl3);
    w.addObject(&floor);
    w.addObject(&right);
    w.addObject(&left);
    w.addObject(&middle);
    //w.addObject(&triangle);

    //camera
    Camera camera(500, 250, 60);
    camera.setTransform(viewTransform(Tuple::Point(0, 1.5, -5),
                                      Tuple::Point(0, 1, 0),
                                      Tuple::Vector(0, 1, 0)));

    //render
    camera.render(w, "out.ppm");

    return 0;
}
