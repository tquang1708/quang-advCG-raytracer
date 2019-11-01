/* prototyping for a command line application
 * mainInteractive.cpp - Interactive world builder
 * Quang Tran - 10/30/19
 * */

#include "baseclass/baseclass_headers.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#include <istream>
#include <sstream>
#include <iostream>
#include <iomanip>

int getInt(int);
double getDouble(double);
std::vector<double> getDoubleList(int, std::vector<double>);

std::shared_ptr<Material> makeMaterial();

int main() {
    //default world and camera
    World mainWorld;
    Camera camera(1280, 720, 60);

    //input
    std::string input;
    //welcome message
    std::cout << "Welcome to the interactive world building wizard!\n";
    std::cout << "Note: (n) in the instruction means give n inputs seperated by a whitespace character.\n";
    std::cout << "Note: (default n) in the instruction means if you do not give an input, the default will be used.\n";
    while (true) {
        std::cout << "Would you like to use the default canvas and camera? (y/n) ";
        std::getline(std::cin, input);
        if (input == "y") {
            //default camera and transformation
            camera.setTransform(viewTransform(Tuple::Point(0, 1.5, -5),
                                              Tuple::Point(0, 1, 0),
                                              Tuple::Vector(0, 1, 0)));

            //set resolution
            while (true) {
                std::cout << "Select resolution (low/mid/high/ultra) ";
                std::getline(std::cin, input);
                if (input == "low") {
                    camera.setHSize(352);
                    camera.setVSize(198);
                    break;
                } else if (input == "mid") {
                    camera.setHSize(480);
                    camera.setVSize(270);
                    break;
                } else if (input == "high") {
                    camera.setHSize(1280);
                    camera.setVSize(720);
                    break;
                } else if (input == "ultra") {
                    camera.setHSize(1920);
                    camera.setVSize(1080);
                    break;
                } else {
                    std::cout << "Bad input.\n";
                }
            }

            //set fov
            while (true) {
                std::cout << "Select FOV (narrow/normal/wide) ";
                std::getline(std::cin, input);
                if (input == "narrow") {
                    camera.setFOV(30);
                    break;
                } else if (input == "normal") {
                    camera.setFOV(60);
                    break;
                } else if (input == "wide") {
                    camera.setFOV(120);
                    break;
                } else {
                    std::cout << "Bad input.\n";
                }
            }

            std::cout << "Default camera set up.\n";
            break;
        } else if (input == "n") {
            int canvas_y;
            int canvas_x;
            double canvas_fov;

            std::cout << "Input Horizontal canvas size (default: 1280) ";
            canvas_x = getInt(1280);
            std::cout << "Input Vertical canvas size (default: 720) ";
            canvas_y = getInt(720);
            std::cout << "Input FOV (default: 60) ";
            canvas_fov = getDouble(60);
            camera.setHSize(canvas_x);
            camera.setVSize(canvas_y);
            camera.setFOV(canvas_fov);

            std::vector<double> from_xyz;
            std::vector<double> to_xyz;
            std::vector<double> up_xyz;
            std::cout << std::endl << "View Transformation setup" << std::endl;
            std::cout << "(3) Camera's viewing from (x y z) (default: 0 1.5 -5) ";
            from_xyz = getDoubleList(3, std::vector<double> {0, 1.5, -5});
            std::cout << "(3) Camera's viewing to (x y z) (default: 0 1 0) ";
            to_xyz = getDoubleList(3, std::vector<double> {0, 1, 0});
            std::cout << "(3) Camera's up vector (x y z) (default: 0 1 0) ";
            up_xyz = getDoubleList(3, std::vector<double> {0, 1, 0});
            camera.setTransform(viewTransform(Tuple::Point(from_xyz[0], from_xyz[1], from_xyz[2]),
                                              Tuple::Point(to_xyz[0], to_xyz[1], to_xyz[2]),
                                              Tuple::Vector(up_xyz[0], up_xyz[1], up_xyz[2])));

            std::cout << "Custom camera set up.\n";
            break;
        } else {
            std::cout << "Bad input.\n";
        }
    }

    //world building wizard
    std::vector<std::shared_ptr<Object>> objectsArray;
    std::vector<std::string> objectsNameArray;
    std::vector<std::string> objectsTypeArray;
    std::vector<std::shared_ptr<Material>> materialsArray;
    std::vector<std::string> materialsNameArray;

    int objectsCount = 0, materialsCount = 0;


    //default material creation
    std::cout << "Creating a default material...\n";
    materialsArray.push_back(makeMaterial());
    materialsNameArray.push_back("default");
    materialsCount += 1;

    WIZ_START:while (true) {
        //commands
        std::cout << "Available commands (add remove list render end) ";
        std::getline(std::cin, input);

        //input handling
        if (input == "render") {
            std::string output;
            std::cout << "Output file name (don't include extension): ";
            std::getline(std::cin, output);
            output = "./output/" + output + ".ppm";
            camera.render(mainWorld, output);
            std::cout << "World rendered.\n";
        } else if (input == "add") {
            while (true) {
                std::cout << "Avaiable objects (material sphere floor triangle) ";
                std::getline(std::cin, input);
                if (input == "material") {
                    std::cout << "New material added.\n";
                    goto WIZ_START;
                } else if (input == "sphere") {
                    std::cout << "New sphere added.\n";
                    goto WIZ_START;
                } else if (input == "floor") {
                    std::cout << "New floor added.\n";
                    goto WIZ_START;
                } else if (input == "triangle") {
                    std::cout << "New triangle added.\n";
                    goto WIZ_START;
                } else {
                    std::cout << "Bad input.\n";
                }
            }
        } else if (input == "remove") {
            while (true) {
                std::cout << "Remove (material/object) ";
                std::getline(std::cin, input);
                int index;
                if (input == "object") {
                    //relist objects
                    std::cout << "ID   Objects   Name\n";
                    for (size_t i = 0; i < objectsNameArray.size(); i++) {
                        std::cout << std::setw(5) << std::left << i
                                  << std::setw(10) << std::left << objectsTypeArray[i]
                                  << objectsNameArray[i] << std::endl;
                    }

                    std::cout << "Input ID of object to remove (default 0) ";
                    index = getInt(0);
                    goto WIZ_START;
                } else if (input == "material") {
                    //relist materials
                    std::cout << "ID   MaterialName\n";
                    for (size_t i = 0; i < materialsNameArray.size(); i++) {
                        std::cout << std::setw(5) << std::left << i
                                  << std::setw(10) << std::left << materialsNameArray[i]
                                  << std::endl;
                    std::cout << "Input ID of material to remove (default 1) ";
                    index = getInt(1);
                    if (index == 0) {std::cout << "Default material cannot be removed.\n";};
                    goto WIZ_START;
                    }
                } else {
                    std::cout << "Bad input.\n";
                }
            }
        } else if (input == "end") {
            std::cout << "Warning: Ending the program would erase all created objects.\n";
            while (true) {
                std::cout << "Are you sure? (y/n) ";
                std::getline(std::cin, input);

                if (input == "y") {
                    std::cout << "Ending program...\n";
                    return 0;
                } else if (input == "n") {
                    goto WIZ_START;
                } else {
                    std::cout << "Bad input.\n";
                }
            }
            break;
        } else if (input == "list") {
            std::cout << "ID   Objects   Name\n";
            for (size_t i = 0; i < objectsNameArray.size(); i++) {
                std::cout << std::setw(5) << std::left << i
                          << std::setw(10) << std::left << objectsTypeArray[i]
                          << objectsNameArray[i] << std::endl;
            }
            std::cout << "---------------------------\n";
            std::cout << "ID   MaterialName\n";
            for (size_t i = 0; i < materialsNameArray.size(); i++) {
                std::cout << std::setw(5) << std::left << i
                          << std::setw(10) << std::left << materialsNameArray[i]
                          << std::endl;
            }
        } else {
            std::cout << "Bad input.\n";
        }
    }
}

//learnt from
//http://www.keithschwarz.com/cs106l/fall2010/course-reader/Ch3_Streams.pdf
//found from this StackOverflow question
//https://stackoverflow.com/questions/4999650/c-how-do-i-check-if-the-cin-buffer-is-empty
int getInt(int defaultVal) {
    while (true) { //read until user enters valid data
        //re-initialize strInp and stringstream objects
        std::string strInp;
        std::stringstream converter;

        std::getline(std::cin, strInp);
        //check for empty string (default)
        if (strInp == "") {
            return defaultVal;
        }

        converter << strInp;

        //check for int
        int out;
        if (converter >> out) { //if converter successfully reads to out
            char remaining;
            if (converter >> remaining) {
                /* if converter successfully reads to remaining
                 * meaning something is there
                 * */
                std::cout << "Bad input. Please input an integer. ";
            } else {
                return out;
            }
        } else {
            std::cout << "Bad input. Please input an integer. ";
        }
    }
}

double getDouble(double defaultVal) {
    while (true) {
        std::string strInp;
        std::stringstream converter;
        std::getline(std::cin, strInp);

        //check for empty string (default)
        if (strInp == "") {
            return defaultVal;
        }

        converter << strInp;

        //check for double;
        double out;
        if (converter >> out) {
            char remaining;

            if (converter >> remaining) {
                std::cout << "Bad input. Please input a double. ";
            } else {
                return out;
            }
        } else {
            std::cout << "Bad input. Please input a double. ";
        }
    }
}

//takes in a length of list then return a list of doubles
std::vector<double> getDoubleList(int listLen, std::vector<double> defaultVal) {
    GET_DOUBLE_LIST_START:while (true) {
        //storing the inputs
        std::string strInp;
        std::stringstream converter;

        std::getline(std::cin, strInp);
        //check for empty string (default)
        if (strInp == "") {
            return defaultVal;
        }
        converter << strInp;

        //reading out from the stringstream
        std::vector<double> outList(listLen);
        for (int i = 0; i < listLen; i++) {
            if (!(converter >> outList[i])) {
                std::cout << "Bad input. Please input a list of " << listLen
                          << " doubles separated by spaces. ";
                goto GET_DOUBLE_LIST_START;
            }
        }

        //check remaining
        char remaining;
        if (converter >> remaining) {
            std::cout << "Bad input. Please input a list of " << listLen
                      << " doubles separated by spaces. ";
        } else {
            return outList;
        }
    }
}

//prompts the user for Material stuffs
//returns a pointer to the corresponding material
std::shared_ptr<Material> makeMaterial() {
    std::shared_ptr<Material> newMaterial = std::make_shared<Material>();

    std::cout << "(3) Input Color (default: 1 1 1) ";
    std::vector<double> color_xyz = getDoubleList(3, std::vector<double> {1, 1, 1});
    newMaterial -> setColor(Color (color_xyz[0], color_xyz[1], color_xyz[2]));

    std::cout << "Input ambient (default: 0.1) ";
    newMaterial -> setAmbient(getDouble(0.1));

    std::cout << "Input diffuse (default: 0.9) ";
    newMaterial -> setDiffuse(getDouble(0.9));

    std::cout << "Input specular (default: 0.9) ";
    newMaterial -> setSpecular(getDouble(0.9));

    std::cout << "Input shininess (default: 200) ";
    newMaterial -> setShininess(getDouble(200));

    std::cout << "Input reflectivity (default: 0.0) ";
    newMaterial -> setReflectivity(getDouble(0));

    std::cout << "Input emission (default: 0.0) ";
    newMaterial -> setEmission(getDouble(0));

    return newMaterial;
}
