/* main.cpp - The main of the program. Used to put things in place
 * Quang Tran - 9/12/2019
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>

//defining canvas size in pixels
const int CANVAS_X = 600;
const int CANVAS_Y = 600;
//defining world's dimension
const float WORLD_X = 4;
const float WORLD_Y = 4;

//translated directly from slide's pseudocode
//and the book's hints
int main(int argc, char** argv) {
    //handling inputs
    std::vector<double> a;
    for (int i = 1; i < argc; i++) {
        a.push_back(atof(argv[i]));
    }

    //making a canvas
    Canvas canvas(CANVAS_X, CANVAS_Y);
    //define red
    Color red(1, 0, 0);
    //define white
    Color white(1, 1, 1);
    //define green
    Color green(0, 1, 0);

    //make a sphere
    Sphere sphere1;
    //setting a material
    Material m1;
    m1.setColor(Color(0.8, 1.0, 0.6));
    m1.setDiffuse(0.7);
    m1.setSpecular(0.2);
    sphere1.setMaterial(m1);
    //sphere1.setTransform(Matrix::Scaling(2, 1, 1));

    //2nd Sphere
    Sphere sphere2;
    Material m2;
    m2.setColor(green);
    sphere2.setMaterial(m2);

    //move it a bit
    sphere2.setTransform(Matrix::Translation(1, 1, 2));

    //light
    PointLight light(Tuple::Point(-10, 10, -10), white);

    //camera
    Tuple camera = Tuple::Point(0, 0, -5);

    double x, y;
    for (double j = 0; j < CANVAS_Y; j++) {
        //iterating over vertical pixels
        //calculating world y
        y = (WORLD_Y / 2) - j / (CANVAS_Y / WORLD_Y);
        for (double i = 0; i < CANVAS_X; i++) {
            //Catching intersections
            //calculating world x
            x = -(WORLD_X / 2) + i / (CANVAS_X / WORLD_X);
            Tuple currPoint = Tuple::Point(x, y, 0);
            Tuple direction = (currPoint - camera).normalize();
            Ray ray(camera, direction);
            std::vector<double> ints = sphere1.intersect(ray);

            //Checking hits
            for (size_t t = 0; t < ints.size(); t++) {
                if (ints[t] > 0) {
                    Tuple hitPoint = ray.position(ints[t]);
                    Color trueColor = lighting(sphere1.getMaterial(),
                                               light,
                                               hitPoint,
                                               sphere1.normalAt(hitPoint),
                                               ray.getOrigin());
                    canvas.write_pixel(i, j, trueColor);
                    break;
                }
            }
        }
    }
    canvas.toPPM("out.ppm");

    return 0;
}
