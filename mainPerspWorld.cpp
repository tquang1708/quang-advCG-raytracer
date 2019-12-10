/* mainPerspWorld.cpp - Main of program with mult obj support
 *
 * Quang Tran - 10/14/2019
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>

int main() {
    //floor
    std::shared_ptr<Plane> floor = std::make_shared<Plane>();
    Material floorMat;
    std::shared_ptr<CheckerPattern> squarePattern = std::make_shared<CheckerPattern>(Color(0.8, 0.8, 0.8), Color(0.2, 0.2, 0.2));
    floorMat.setPattern(squarePattern);
    floorMat.setSpecular(0);
    floorMat.setReflectivity(0.3);
    floor -> setMaterial(floorMat);

    //wall1
    std::shared_ptr<Plane> wall1 = std::make_shared<Plane>();
    Material wall1Mat;
    std::shared_ptr<StripePattern> testPattern =
        std::make_shared<StripePattern>(std::vector<Color>{
                Color(0.9, 0.9, 0.9), Color(0.7, 0.7, 0.7), Color(0.5, 0.5, 0.5),
                Color(0.3, 0.3, 0.3), Color(0.1, 0.1, 0.1), Color(0.2, 0.2, 0.2),
                Color(0.4, 0.4, 0.4), Color(0.6, 0.6, 0.6), Color(0.8, 0.8, 0.8)});
    testPattern -> setTransform(Matrix::Rotation('y', -45) * Matrix::Scaling(0.1, 0.1, 0.1));
    wall1 -> setTransform(Matrix::Translation(0, 0, 30) * Matrix::Rotation('y', -45) * Matrix::Rotation('x', 90));
    wall1Mat.setPattern(testPattern);
    wall1Mat.setSpecular(0);
    wall1 -> setMaterial(wall1Mat);

    //floor2
    std::shared_ptr<Plane> wall2 = std::make_shared<Plane>();
    Material wall2Mat;
    std::shared_ptr<StripePattern> testPattern2 =
        std::make_shared<StripePattern>(std::vector<Color>{
                Color(0.9, 0.9, 0.9), Color(0.7, 0.7, 0.7), Color(0.5, 0.5, 0.5),
                Color(0.3, 0.3, 0.3), Color(0.1, 0.1, 0.1), Color(0.2, 0.2, 0.2),
                Color(0.4, 0.4, 0.4), Color(0.6, 0.6, 0.6), Color(0.8, 0.8, 0.8)});
    testPattern2 -> setTransform(Matrix::Rotation('y', 45) * Matrix::Scaling(0.1, 0.1, 0.1) * Matrix::Translation(1, 1, 1));
    wall2 -> setTransform(Matrix::Translation(0, 0, 30) * Matrix::Rotation('y', 45) * Matrix::Rotation('x', 90));
    wall2Mat.setPattern(testPattern2);
    wall2Mat.setSpecular(0);
    wall2 -> setMaterial(wall2Mat);

    //mid sphere
    std::shared_ptr<Sphere> middle = std::make_shared<Sphere>();
    middle -> setTransform(Matrix::Translation(1, 1, 0));
    Material ms;
    ms.setTransparency(1.0);
    ms.setRefractiveIndex(1.5);
    ms.setAmbient(0);
    ms.setDiffuse(0);
    ms.setColor(Color(0.9, 0.5, 0.6));
    middle -> setMaterial(ms);

    //back sphere
    std::shared_ptr<Sphere> halfbehind = std::make_shared<Sphere>();
    halfbehind -> setTransform(Matrix::Translation(-1, 0.5, 10) * Matrix::Scaling(0.5, 0.5, 0.5));
    Material halfbehindMat;
    halfbehindMat.setColor(Color(0.5, 0.95, 0.1));
    halfbehind -> setMaterial(halfbehindMat);

    //far back sphere
    std::shared_ptr<Sphere> behind = std::make_shared<Sphere>();
    behind -> setTransform(Matrix::Translation(-3, 1.5, 20) * Matrix::Scaling(1.5, 1.5, 1.5));
    Material bs;
    bs.setColor(Color(0.6, 0.8, 0.3));
    behind -> setMaterial(bs);

    //point light
    std::shared_ptr<AreaLight> pl1 = std::make_shared<AreaLight>(Tuple::Point(-10, 10, -10), Tuple::Point(-10, 10, -10), Tuple::Point(-10, 10, -10), 1, 1, Color(1, 1, 1));

    //world
    World w;
    w.addLight(pl1);
    w.addObject(floor);
    w.addObject(wall1);
    w.addObject(wall2);
    w.addObject(middle);
    //w.addObject(halfbehind);
    //w.addObject(behind);

    //camera
    Camera camera(640, 360, 60, 0, -1, 1, 1);
    camera.setTransform(viewTransform(Tuple::Point(0, 1.5, -5),
                                      Tuple::Point(0, 1, 0),
                                      Tuple::Vector(0, 1, 0)));
    //aa
    camera.aaOn = false;
    //render
    camera.render(w, "output/test.ppm");

    return 0;
}
