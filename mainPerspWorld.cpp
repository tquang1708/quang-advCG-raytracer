/* mainPerspWorld.cpp - Main of program with mult obj support
 * Quang Tran - 10/14/2019
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>

//defining canvas size in pixels
const int CANVAS_X = 600;
const int CANVAS_Y = 600;
//defining world's dimension
const float WORLD_X = 4;
const float WORLD_Y = 4;

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

    //mid sphere
    Sphere middle;
    middle.setTransform(Matrix::Translation(-0.5, 1, 0.5));
    Material ms;
    ms.setColor(Color(0.1, 1, 0.5));
    ms.setDiffuse(0.7);
    ms.setSpecular(0.3);
    middle.setMaterial(ms);

    //right sphere
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
    PointLight pl2(Tuple::Point(10, 10, -10), Color(1, 1, 1));

    //world
    World w;
    //w.addLight(&pl1);
    w.addLight(&pl2);
    w.addObject(&floor);
    w.addObject(&right);
    w.addObject(&left);
    w.addObject(&middle);

    //camera
    Camera camera(500, 250, 60);
    camera.setTransform(viewTransform(Tuple::Point(0, 1.5, -5),
                                      Tuple::Point(0, 1, 0),
                                      Tuple::Vector(0, 1, 0)));

    //render
    camera.render(w, "outLightRight.ppm");

    return 0;
}
