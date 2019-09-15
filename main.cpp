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
    Canvas canvas(100, 100);
    //define red
    Color red(1, 0, 0);
    //make a sphere
    Sphere sphere;

    int x, y;
    for (int j = 0; j < 100; j++) {
        //calculating world y
        y = 2 - j / 25;
        for (int i = 0; i < 100; i++) {
            //Catching intersections
            //calculating world x
            x = -2 + i / 25;
            Tuple origin = Tuple::Point(2, -.4, -5);
            Tuple direction = Tuple::Vector(0, 0, 1);
            Ray ray(origin, direction);
            std::vector<double> ints = sphere.intersect(ray);

            //Checking hits
            bool wasHit = false;
            for (unsigned long t = 0; t < ints.size(); t++) {
                if (ints[t] > 0) {
                    wasHit = true;
                }
            }

            if (wasHit) {
                canvas.write_pixel(i, j, red);
            }
        }
    }
    canvas.toPPM();

    return 0;
}
