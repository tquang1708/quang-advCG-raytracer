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

    //default world
    World w = World::DefaultWorld();

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
            Tuple currPoint = Tuple::Point(x, y, 0);
            Tuple direction = (currPoint - camera).normalize();
            Ray ray(camera, direction);
            Color c = w.colorAt(ray);
            canvas.write_pixel(i, j, c);
        }
    }
    canvas.toPPM("out.ppm");

    return 0;
}
