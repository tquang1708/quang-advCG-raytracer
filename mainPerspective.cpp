/* main.cpp - The main of the program. Used to put things in place
 * Quang Tran - 9/12/2019
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>

//defining canvas size in pixels
const int CANVAS_X = 300;
const int CANVAS_Y = 300;
//defining world's dimension
const float WORLD_X = 4;
const float WORLD_Y = 4;

//translated directly from slide's pseudocode
//and the book's hints
int main() {
    //making a canvas
    Canvas canvas(CANVAS_X, CANVAS_Y);
    //define red
    Color red(1, 0, 0);
    //define white
    Color white(1, 1, 1);
    //make a sphere
    Sphere sphere;
    //setting a material
    Material m;
    m.setColor(red);
    m.setDiffuse(1);
    m.setAmbient(0.2);
    m.setShininess(0.8);
    m.setEmission(0);
    sphere.setMaterial(m);

    //light
    PointLight light(Tuple::Point(-2, 2, 5), white);

    //camera
    Tuple camera = Tuple::Point(1, -1, -5);

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
            std::vector<double> ints = sphere.intersect(ray);

            //Checking hits
            for (size_t t = 0; t < ints.size(); t++) {
                if (ints[t] > 0) {
                    Tuple hitPoint = ray.position(ints[t]);
                    Color trueColor = lighting(sphere.getMaterial(),
                                               light,
                                               hitPoint,
                                               sphere.normalAt(hitPoint));
                    canvas.write_pixel(i, j, trueColor);
                }
            }
        }
    }
    canvas.toPPM("output/out9.ppm");

    return 0;
}
