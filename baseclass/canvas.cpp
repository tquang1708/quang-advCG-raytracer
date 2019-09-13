/* canvas.cpp - implementation of functions in canvas.hpp header
 * Quang Tran - 9/11/19
 * */

#include "headers/canvas.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

#include <string>
#include <sstream>

Canvas::Canvas(int width_, int height_) {
    width = width_;
    height = height_;
    //vector array resizing found here
    //https://stackoverflow.com/questions/20047684/how-can-i-resize-a-2d-c-vector?rq=1
    pixel_grid.resize(width, std::vector<Color>(height, Color(0, 0, 0)));
}

//getter funcs
int Canvas::getWidth() const {
    return width;
}

int Canvas::getHeight() const {
    return height;
}

Color Canvas::pixel_at(int w, int h) const {
    return pixel_grid[w][h];
}

//other funcs
//write_pixel
void Canvas::write_pixel(int w, int h, Color c) {
    pixel_grid[w][h] = c;
}

//toPPM
//void Canvas::toPPM() {
void Canvas::toPPM() {
    //file handling found here
    //http://www.cplusplus.com/doc/tutorial/files/
    std::ofstream outPPM("out.ppm");
    outPPM << "P3\n" << width << " " << height << "\n" << "255\n";
    for (int h = 0; h < height; h++) {
        std::ostringstream lineStr;
        for (int w = 0; w < width; w++) {
            Color color255 = pixel_grid[w][h] * 255;
            //Red
            if (color255.getR() > 255) {
                lineStr << "255 ";
            }
            else if (color255.getR() < 0) {
                lineStr << "0 ";
            }
            else {
                lineStr << round(color255.getR()) << " ";
            }

            //Green
            if (color255.getG() > 255) {
                lineStr << "255 ";
            }
            else if (color255.getG() < 0) {
                lineStr << "0 ";
            }
            else {
                lineStr << round(color255.getG()) << " ";
            }

            //Blue
            if (color255.getB() > 255) {
                lineStr << "255 ";
            }
            else if (color255.getB() < 0) {
                lineStr << "0 ";
            }
            else {
                lineStr << round(color255.getB()) << " ";
            }
        }
        //a lot of help with string splitting from here
        //http://www.cplusplus.com/forum/general/195355/
        //istringstream for splitting into words
        std::istringstream splitter(lineStr.str());
        std::string word;
        int lineLen = 70;
        while(splitter >> word) {
            //if linelen - lenword - 1(space) > 0
            //append word to outPPM
            //else
            //seek back and remove trailing space
            //append newline, then append word
            //reset linelen to 70
            if ((lineLen - int(word.length()) - 1) > 0) {
                outPPM << word << " ";
                lineLen = lineLen - word.length() - 1;
            } else {
                outPPM.seekp(-1, outPPM.cur);
                outPPM << "\n" << word << " ";
                lineLen = 70;
            }
        }
        outPPM.seekp(-1, outPPM.cur);
        outPPM << std::endl;
    }
    outPPM.close();
}
