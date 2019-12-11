/* mainPerspWorld.cpp - Main of program with mult obj support
 *
 * Quang Tran - 10/14/2019
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>

int main() {
    //first plane
    std::shared_ptr<Plane> floor = std::make_shared<Plane>();
    std::shared_ptr<CheckerPattern> bwChecker = std::make_shared<CheckerPattern>(Color(0.8, 0.8, 0.8), Color(0.2, 0.2, 0.2));
    Material floorMat;
    floorMat.setSpecular(0);
    floorMat.setPattern(bwChecker);
    floor -> setMaterial(floorMat);

    //borderwall1
    std::shared_ptr<Plane> borderWall1 = std::make_shared<Plane>();
    std::shared_ptr<StripePattern> gradientStripe1 = std::make_shared<StripePattern>(std::vector<Color>{Color(0.1, 0.1, 0.1), Color(0.3, 0.3, 0.3), Color(0.5, 0.5, 0.5),
            Color(0.7, 0.7, 0.7), Color(0.9, 0.9, 0.9), Color(0.8, 0.8, 0.8), Color(0.6, 0.6, 0.6), Color(0.4, 0.4, 0.4), Color(0.2, 0.2, 0.2)});
    gradientStripe1 -> setTransform(Matrix::Scaling(0.1, 0.1, 0.1) * Matrix::Rotation('y', 45));
    Material borderMat1;
    borderMat1.setSpecular(0);
    borderMat1.setPattern(gradientStripe1);
    borderWall1 -> setMaterial(borderMat1);
    borderWall1 -> setTransform(Matrix::Translation(0, 0, 40) * Matrix::Rotation('y', 45) * Matrix::Rotation('x', 90));

    //borderwall2
    std::shared_ptr<Plane> borderWall2 = std::make_shared<Plane>();
    std::shared_ptr<StripePattern> gradientStripe2 = std::make_shared<StripePattern>(std::vector<Color>{Color(0.1, 0.1, 0.1), Color(0.3, 0.3, 0.3), Color(0.5, 0.5, 0.5),
            Color(0.7, 0.7, 0.7), Color(0.9, 0.9, 0.9), Color(0.8, 0.8, 0.8), Color(0.6, 0.6, 0.6), Color(0.4, 0.4, 0.4), Color(0.2, 0.2, 0.2)});
    gradientStripe2 -> setTransform(Matrix::Scaling(0.1, 0.1, 0.1) * Matrix::Rotation('y', -45));
    Material borderMat2;
    borderMat2.setSpecular(0);
    borderMat2.setPattern(gradientStripe2);
    borderWall2 -> setMaterial(borderMat2);
    borderWall2 -> setTransform(Matrix::Translation(0, 0, 40) * Matrix::Rotation('y', -45) * Matrix::Rotation('x', 90));

    //glasspane1
    std::shared_ptr<Plane> glassPane1 = std::make_shared<Plane>();
    Material glassPane1Mat;
    glassPane1Mat.setSpecular(0);
    glassPane1Mat.setColor(Color(1.0, 1.0, 1.0));
    glassPane1Mat.setTransparency(1.0);
    glassPane1Mat.setRefractiveIndex(1.5);
    glassPane1Mat.setReflectivity(0.3);
    glassPane1Mat.setAmbient(0.0);
    glassPane1Mat.setDiffuse(0.1);
    glassPane1Mat.setSpecular(0.9);
    glassPane1 -> setMaterial(glassPane1Mat);
    glassPane1 -> setTransform(Matrix::Translation(0, 5, 10) * Matrix::Rotation('y', -45) * Matrix::Rotation('x', 110));

    //frontsphere
    std::shared_ptr<Sphere> frontSphere = std::make_shared<Sphere>();
    Material frontSphereMat;
    frontSphereMat.setColor(Color(1.0, 0.9, 0.9));
    frontSphereMat.setRefractiveIndex(2.147);
    frontSphereMat.setTransparency(1.0);
    frontSphereMat.setReflectivity(0.9);
    frontSphereMat.setDiffuse(0.3);
    frontSphereMat.setAmbient(0.1);
    frontSphereMat.setSpecular(1.0);
    frontSphere -> setMaterial(frontSphereMat);
    frontSphere -> setTransform(Matrix::Translation(2.5, 1, -3));

    //backdia
    std::shared_ptr<Sphere> backDia = std::make_shared<Sphere>();
    Material backDiaMat;
    backDiaMat.setColor(Color(0.95, 0.95, 0.95));
    backDiaMat.setRefractiveIndex(2.147);
    backDiaMat.setTransparency(0.9);
    backDiaMat.setReflectivity(0.9);
    backDiaMat.setDiffuse(0.2);
    backDiaMat.setAmbient(0.1);
    backDiaMat.setSpecular(1.0);
    backDiaMat.setShininess(3000);
    backDia -> setMaterial(backDiaMat);
    backDia -> setTransform(Matrix::Translation(2, 1.5, 2) * Matrix::Scaling(1.5, 1.5, 1.5));

    //skylight
    std::shared_ptr<Sphere> skySun = std::make_shared<Sphere>();
    Material skySunMat;
    skySunMat.setColor(Color(0.95, 0.85, 0.2));
    skySunMat.setEmission(0.5);
    skySun -> setMaterial(skySunMat);
    skySun -> setTransform(Matrix::Translation(6, 5, 2) * Matrix::Scaling(2.5, 2.5, 2.5));

    //behindglass1
    std::shared_ptr<Sphere> behindGlass1 = std::make_shared<Sphere>();
    Material bGlass1Mat;
    bGlass1Mat.setColor(Color(0.9, 0.2, 0.9));
    bGlass1Mat.setRefractiveIndex(1.5);
    bGlass1Mat.setTransparency(1.0);
    bGlass1Mat.setDiffuse(0.1);
    bGlass1Mat.setAmbient(0.1);
    behindGlass1 -> setMaterial(bGlass1Mat);
    behindGlass1 -> setTransform(Matrix::Translation(-1, 3, 13) * Matrix::Scaling(3, 3, 3));

    //frontsphere
    std::shared_ptr<Sphere> frontSphere2 = std::make_shared<Sphere>();
    Material frontSphere2Mat;
    frontSphere2Mat.setColor(Color(0.1, 0.1, 0.1));
    frontSphere2Mat.setRefractiveIndex(1.5);
    frontSphere2Mat.setTransparency(1.0);
    frontSphere2Mat.setDiffuse(0.2);
    frontSphere2Mat.setAmbient(0.1);
    frontSphere2Mat.setSpecular(1.0);
    frontSphere2Mat.setShininess(300);
    frontSphere2 -> setMaterial(frontSphere2Mat);
    frontSphere2 -> setTransform(Matrix::Translation(0, 0, -3));

    //inglass
    std::shared_ptr<Sphere> inGlass = std::make_shared<Sphere>();
    Material inGlassMat;
    inGlassMat.setColor(Color(0.1, 0.2, 0.7));
    inGlassMat.setRefractiveIndex(1.333);
    inGlassMat.setTransparency(0.9);
    inGlassMat.setDiffuse(0.1);
    inGlassMat.setAmbient(0.1);
    inGlassMat.setSpecular(0.9);
    inGlassMat.setShininess(250);
    inGlass -> setMaterial(inGlassMat);
    inGlass -> setTransform(Matrix::Translation(-3, 3, 2) * Matrix::Scaling(3, 3, 3));

    std::shared_ptr<Sphere> finalSphere = std::make_shared<Sphere>();
    Material finalMat;
    finalMat.setColor(Color(0.9, 0.6, 0.2));
    finalSphere -> setMaterial(finalMat);
    finalSphere -> setTransform(Matrix::Translation(-2.5, 1, -2.5) *  Matrix::Scaling(1, 1, 1));

    //lights
    std::shared_ptr<AreaLight> al1 = std::make_shared<AreaLight>(Tuple::Point(-10, 10, -10), Tuple::Point(-8, 10, -10), Tuple::Point(-10, 12, -10), 4, 4, Color(0.9, 0.5, 0.5));
    std::shared_ptr<AreaLight> al2 = std::make_shared<AreaLight>(Tuple::Point(11, 4, -10), Tuple::Point(11, 6, -10), Tuple::Point(13, 4, -10), 4, 4, Color(0.5, 0.9, 0.5));
    std::shared_ptr<AreaLight> al3 = std::make_shared<AreaLight>(Tuple::Point(4, 12, 12), Tuple::Point(4, 13, 11), Tuple::Point(5, 12, 11), 4, 4, Color(0.5, 0.5, 0.9));

    //world
    World w;
    w.addObject(floor);
    w.addObject(borderWall1);
    w.addObject(borderWall2);
    w.addObject(glassPane1);
    w.addObject(frontSphere);
    //w.addObject(backDia);
    //w.addObject(skySun);
    //w.addObject(behindGlass1);
    //w.addObject(frontSphere2);
    //w.addObject(inGlass);
    //w.addObject(finalSphere);

    w.addLight(al1);
    w.addLight(al2);
    w.addLight(al3);

    //camera
    Camera camera(320, 180, 120, 0.003, -1, 4, 16);
    camera.setTransform(viewTransform(Tuple::Point(0, 1.5, -5),
                                      Tuple::Point(0, 1, 0),
                                      Tuple::Vector(0, 1, 0)));
    //aa
    camera.aaOn = true;
    //render
    camera.render(w, "output/finalPresentation/progress180.ppm");

    return 0;
}
