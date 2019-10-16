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

    //making canvas
    Canvas canvas(CANVAS_X, CANVAS_Y);

    //floor
    Sphere floor;
    floor.setTransform(Matrix::Scaling(10, 0.01, 10));
    Material mf;
    mf.setColor(Color(1, 0.9, 0.9));
    mf.setSpecular(0);
    floor.setMaterial(mf);

    //left wall
    Sphere leftWall;
    leftWall.setTransform(Matrix::Translation(0, 0, 5) * Matrix::Rotation('y', -45) * Matrix::Rotation('x', 90) * Matrix::Scaling(10, 0.01, 10));
    leftWall.setMaterial(mf);

    //right wall
    Sphere rightWall;
    rightWall.setTransform(Matrix::Translation(0, 0, 5) * Matrix::Rotation('y', 45) * Matrix::Rotation('x', 90) * Matrix::Scaling(10, 0.01, 10));
    rightWall.setMaterial(mf);

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
    PointLight pl(Tuple::Point(-10, 10, -10), Color(1, 1, 1));

    //world
    World w;
    w.addLight(&pl);
    w.addObject(&floor);
    w.addObject(&leftWall);
    w.addObject(&rightWall);
    w.addObject(&right);
    w.addObject(&left);
    w.addObject(&middle);

    //camera
    Tuple camera = Tuple::Point(0, 0, -5);

    double x, y;
    for (double j = 0; j < CANVAS_Y; j++) {
        //iterate over vert pixels
        //calc world y
        y = (WORLD_Y / 2) - j / (CANVAS_Y / WORLD_Y);
        for (double i = 0; i < CANVAS_X; i++) {
            //calc world x
            x = -(WORLD_X / 2) + i / (CANVAS_X / WORLD_X);
            Tuple currPoint = Tuple::Point(x, y, -4);
            Tuple direction = (currPoint - camera).normalize();
            Ray ray(camera, direction);
            Color c = w.colorAt(ray);
            canvas.write_pixel(i, j, c);
        }
    }
    canvas.toPPM("out.ppm");

    return 0;
}
