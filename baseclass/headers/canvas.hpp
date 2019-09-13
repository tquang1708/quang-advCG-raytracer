/* canvas.hpp - header file for canvas, the object to draw pixels on to
 *
 * Quang Tran - 9/11/19
 * */

#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "color.hpp"
#include <vector>
#include <string>

class Canvas {
    private:
        int width;
        int height;
        std::vector<std::vector<Color>> pixel_grid;
    public:
        //constructors
        Canvas(int width_, int height_);

        //getter functions
        int getWidth() const;
        int getHeight() const;
        Color pixel_at(int w, int h) const;

        //other functions
        void write_pixel(int w, int h, Color c);
        void toPPM();
};

#endif
