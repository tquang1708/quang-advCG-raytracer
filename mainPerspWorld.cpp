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
    std::shared_ptr<Plane> floor = std::make_shared<Plane>();
    Material mf;
    mf.setColor(Color(1, 0.9, 0.9));
    mf.setSpecular(0.5);
    floor -> setMaterial(mf);

    //leftwall
    std::shared_ptr<Plane> leftwall = std::make_shared<Plane>();
    Material mlw;
    mlw.setColor(Color(0.9, 0.5, 0.4));
    mlw.setSpecular(0);
    leftwall -> setMaterial(mlw);
    leftwall -> setTransform(Matrix::Translation(0, 0, 5) * Matrix::Rotation('y', 45) * Matrix::Rotation('x', 90));

    //mid sphere
    std::shared_ptr<Sphere> middle = std::make_shared<Sphere>();
    middle -> setTransform(Matrix::Translation(-0.5, 1, 0.5)
                         * Matrix::Scaling(1, 2, 1));
    Material ms;
    ms.setColor(Color(0.1, 1, 0.5));
    ms.setDiffuse(0.7);
    ms.setSpecular(0.3);
    ms.setEmission(0.4);
    middle -> setMaterial(ms);

    //left sphere
    std::shared_ptr<Sphere> left = std::make_shared<Sphere>();
    left -> setTransform(Matrix::Translation(0.75, 2, -0.25) * Matrix::Scaling(1, 1.5, 2));
    Material msl;
    msl.setColor(Color(0.2, 0.4, 0.6));
    msl.setDiffuse(0.3);
    msl.setSpecular(0.9);
    left -> setMaterial(msl);

    //point light
    std::shared_ptr<PointLight> pl1 = std::make_shared<PointLight>(Tuple::Point(-10, 0, -10), Color(1, 1, 1));

    //world
    World w;
    w.addLight(pl1);
    w.addObject(floor);
    w.addObject(leftwall);
    w.addObject(middle);
    w.addObject(left);

    //camera
    Camera camera(800, 480, 90);
    camera.setTransform(viewTransform(Tuple::Point(0, 1.5, -5),
                                      Tuple::Point(0, 1, 0),
                                      Tuple::Vector(0, 1, 0)));

    //render
    camera.render(w, "output/out.ppm");

    return 0;
}
