/* main.cpp - The main of the program. Used to put things in place
 * Quang Tran - 9/12/2019
 * */

#include "baseclass/baseclass_headers.hpp"

int main() {
    Canvas c(5, 3);
    Color c1(1.5, 0, 0);
    Color c2(0, 0.5, 0);
    Color c3(-0.5, 0, 1);
    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);
    c.toPPM();
    return 0;
}
