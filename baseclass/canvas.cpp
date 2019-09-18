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

Canvas::Canvas(int w, int h): width(w), height(h) {
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

//clamp value
//for clamping pixels
int Canvas::clampValue(int val) {
    val > 255 ? val = 255 : val;
    val < 0 ? val = 0 : val;
    return val;
}

//toPPM
//void Canvas::toPPM() {
//suggestion on not hard coding filename from Ulysses
void Canvas::toPPM(std::string filename) {
    //file handling found here
    //http://www.cplusplus.com/doc/tutorial/files/
    std::ofstream outPPM(filename);
    outPPM << "P3\n" << width << " " << height << "\n" << "255\n";
    for (int h = 0; h < height; h++) {
        std::ostringstream lineStr;
        for (int w = 0; w < width; w++) {
            Color color255 = pixel_grid[w][h] * 255;
            lineStr << clampValue(color255.getR()) << " ";
            lineStr << clampValue(color255.getG()) << " ";
            lineStr << clampValue(color255.getB()) << " ";
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
