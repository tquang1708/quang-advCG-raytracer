/* mainPerspWorld.cpp - Main of program with mult obj support
 * Quang Tran - 10/14/2019
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>

int main() {
    //floor
    std::shared_ptr<Plane> floor = std::make_shared<Plane>();
    std::shared_ptr<StripePattern> testPattern =
           std::make_shared<StripePattern>(std::vector<Color>{Color(0.9, 1.0, 1.0), Color(0.1, 0.2, 0.1), Color(1.0, 0.9, 1.0), Color(0.2, 0.1, 0.1)});
    //std::shared_ptr<TestPattern> testPattern = std::make_shared<TestPattern>();
    testPattern -> setTransform(Matrix::Rotation('y', 45) * Matrix::Scaling(0.1, 0.1, 0.1));
    Material mf;
    mf.setColor(Color(1, 0.9, 0.9));
    mf.setSpecular(0);
    mf.setReflectivity(0.2);
    mf.setPattern(testPattern);
    floor -> setMaterial(mf);

    //mid sphere
    std::shared_ptr<Sphere> middle = std::make_shared<Sphere>();
    middle -> setTransform(Matrix::Translation(0, 1, 0));
    Material ms;
    ms.setColor(Color(1, 1, 1));
    ms.setTransparency(1.0);
    ms.setRefractiveIndex(1.5);
    ms.setReflectivity(1.0);
    //ms.setPattern(testPattern);
    middle -> setMaterial(ms);

    //midmid sphere
    std::shared_ptr<Sphere> left = std::make_shared<Sphere>();
    left -> setTransform(Matrix::Translation(0, 1, 0) * Matrix::Scaling(0.5, 0.5, 0.5));
    Material msl;
    msl.setColor(Color(1.0, 1.0, 1.0));
    msl.setRefractiveIndex(1.0);
    msl.setTransparency(1.0);
    left -> setMaterial(msl);

    //back sphere
    std::shared_ptr<Sphere> behind = std::make_shared<Sphere>();
    behind -> setTransform(Matrix::Translation(-0.5, 2, 3) * Matrix::Scaling(1.5, 1.5, 1.5));
    Material bs;
    bs.setColor(Color(1, 0.9, 0.9));
    bs.setDiffuse(0.7);
    bs.setSpecular(0.9);
    bs.setReflectivity(0.9);
    //bs.setPattern(testPattern);
    behind -> setMaterial(bs);

    //point light
    std::shared_ptr<PointLight> pl1 = std::make_shared<PointLight>(Tuple::Point(-10, 10, -10), Color(1, 1, 1));

    //world
    World w;
    w.addLight(pl1);
    w.addObject(floor);
    w.addObject(middle);
    //w.addObject(left);
    //w.addObject(behind);

    //camera
    Camera camera(1280, 720, 60);
    camera.setTransform(viewTransform(Tuple::Point(0, 1.5, -5),
                                      Tuple::Point(0, 1, 0),
                                      Tuple::Vector(0, 1, 0)));
    //aa
    camera.aaOn = true;
    //render
    camera.render(w, "output/test.ppm");

    return 0;
}
