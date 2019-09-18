/* main.cpp - The main of the program. Used to put things in place
 * Quang Tran - 9/12/2019
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>

//first image rendering
//translated directly from slide's pseudocode
//and the book's hints
int main() {
    //making a 100x100 canvas
    Canvas canvas(1000, 1000);
    //defining a world edge's length (size)
    const float WORLD_SIZE = 3;
    //define red
    Color red(1, 0, 0);
    //define white
    Color white(1, 1, 1);
    //make a sphere
    Sphere sphere;
    //setting a material
    Material m;
    m.setColor(red);
    sphere.setMaterial(m);

    //light
    PointLight light(Tuple::Point(-2, 2, 5), white);

    double x, y;
    for (double j = 0; j < 1000; j++) {
        //iterating over vertical pixels
        //calculating world y
        y = (WORLD_SIZE / 2) - j / (1000 / WORLD_SIZE);
        for (double i = 0; i < 1000; i++) {
            //Catching intersections
            //calculating world x
            x = -(WORLD_SIZE / 2) + i / (1000 / WORLD_SIZE);
            Tuple origin = Tuple::Point(x, y, -5);
            Tuple direction = Tuple::Vector(0, 0, 1);
            Ray ray(origin, direction);
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
    canvas.toPPM("out.ppm");

    return 0;
}
