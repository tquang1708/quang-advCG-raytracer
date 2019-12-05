/* mainPerspWorld.cpp - Main of program with mult obj support
 * Quang Tran - 10/14/2019
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>

int main() {
    //floor
    std::shared_ptr<Plane> floor = std::make_shared<Plane>();
    Material mf;
    mf.setColor(Color(1, 0.9, 0.9));
    mf.setSpecular(0);
    mf.setReflectivity(0.8);
    floor -> setMaterial(mf);

    //mid sphere
    std::shared_ptr<Sphere> middle = std::make_shared<Sphere>();
    middle -> setTransform(Matrix::Translation(-0.5, 1, 0.5));
    Material ms;
    ms.setColor(Color(0.1, 0.5, 0.2));
    ms.setDiffuse(0.8);
    ms.setSpecular(0.3);
    ms.setTransparency(1.0);
    ms.setRefractiveIndex(1.5);
    middle -> setMaterial(ms);

    //midmid sphere
    std::shared_ptr<Sphere> left = std::make_shared<Sphere>();
    left -> setTransform(Matrix::Translation(-0.5, 1, 0.5) * Matrix::Scaling(0.25, 0.25, 0.25));
    Material msl;
    msl.setColor(Color(0.5, 0.1, 0.2));
    msl.setDiffuse(0.9);
    msl.setSpecular(0.9);
    msl.setShadowCast(false);
    msl.setRefractiveIndex(2.147);
    msl.setTransparency(0.9);
    left -> setMaterial(msl);

    //back sphere
    std::shared_ptr<Sphere> behind = std::make_shared<Sphere>();
    behind -> setTransform(Matrix::Translation(-0.5, 2, 3) * Matrix::Scaling(1.5, 1.5, 1.5));
    Material bs;
    bs.setColor(Color(1, 0.8, 0.1));
    bs.setDiffuse(0.7);
    bs.setSpecular(0.9);
    bs.setReflectivity(0.9);
    behind -> setMaterial(bs);

    //point light
    std::shared_ptr<PointLight> pl1 = std::make_shared<PointLight>(Tuple::Point(-10, 10, -10), Color(1, 1, 1));

    //world
    World w;
    w.addLight(pl1);
    w.addObject(floor);
    w.addObject(middle);
    w.addObject(left);
    w.addObject(behind);

    //camera
    Camera camera(853, 480, 60);
    camera.setTransform(viewTransform(Tuple::Point(0, 1.5, -5),
                                      Tuple::Point(0, 1, 0),
                                      Tuple::Vector(0, 1, 0)));

    //render
    camera.render(w, "output/test.ppm");

    return 0;
}
