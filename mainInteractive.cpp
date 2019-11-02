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
std::shared_ptr<Matrix> makeMatrix(std::string);

void listObjects(std::vector<std::string> *, std::vector<std::string> *);
void listMaterials(std::vector<std::string> *);
void listMatrices(std::vector<std::string> *, std::vector<std::string> *);

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

    std::vector<std::shared_ptr<PointLight>> lightsArray;
    std::vector<std::string> lightsNameArray;
    std::vector<std::string> lightsTypeArray;

    std::vector<std::shared_ptr<Material>> materialsArray;
    std::vector<std::string> materialsNameArray;

    std::vector<std::shared_ptr<Matrix>> matricesArray;
    std::vector<std::string> matricesNameArray;
    std::vector<std::string> matricesTypeArray;

    //default material creation
    std::cout << "Creating a default material...\n";
    materialsArray.push_back(makeMaterial());
    materialsNameArray.push_back("default");

    //default matrix creation
    std::cout << "Creating a default transformation matrix...\n";
    std::cout << "The default transformation matrix is an identity matrix.\n";
    matricesArray.push_back(makeMatrix("Identity"));
    matricesNameArray.push_back("identity");
    matricesTypeArray.push_back("Translation");

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
                std::cout << "Avaiable objects (material matrix pointlight sphere floor triangle) ";
                std::getline(std::cin, input);
                if (input == "material") {
                    //Material interaction
                    std::cout << "Creating a new material...\n";
                    materialsArray.push_back(makeMaterial());
                    std::cout << "Input material name ";
                    std::getline(std::cin, input);
                    materialsNameArray.push_back(input);
                    std::cout << "New material added.\n";
                    goto WIZ_START;
                //add a new matrix
                } else if (input == "matrix") {
                    std::cout << "Creating a new matrix...\n";

                    //find matrix type
                    while (true) {
                        std::cout << "Input matrix type (Translation/Scaling/Rotation) ";
                        std::getline(std::cin, input);
                        if ((input != "Translation") and (input != "Scaling") and (input != "Rotation")) {
                            std::cout << "Bad input.\n";
                        }
                        else {
                            goto MAKE_MATRIX;
                        }
                    }

                    MAKE_MATRIX:matricesArray.push_back(makeMatrix(input));
                    matricesTypeArray.push_back(input);
                    std::cout << "Input matrix name ";
                    std::getline(std::cin, input);
                    matricesNameArray.push_back(input);
                    std::cout << "New matrix added.\n";
                    goto WIZ_START;
                } else if (input == "pointlight") {
                    std::cout << "Creating a new point light...\n";
                    lightsArray.push_back(makePointLight());
                    mainWorld.addLight(lightsArray[lightsArray.size() - 1]);
                    std::cout << "Input point light name ";
                    std::getline(std::cin, input);
                    lightsNameArray.push_back(input);
                    lightsTypeArray.push_back("Point");
                    std::cout << "New point light added.\n";
                    goto WIZ_START;
                //add a new sphere
                } else if (input == "sphere") {
                    std::cout << "Creating a new sphere...\n";
                    std::cout << "New sphere added.\n";
                    goto WIZ_START;
                //add a new floor
                } else if (input == "floor") {
                    std::cout << "New floor added.\n";
                    goto WIZ_START;
                //add a new triangle
                } else if (input == "triangle") {
                    std::cout << "New triangle added.\n";
                    goto WIZ_START;
                } else {
                    std::cout << "Bad input.\n";
                }
            }
        } else if (input == "remove") {
            while (true) {
                std::cout << "Remove (material/matrix/object/light) ";
                std::getline(std::cin, input);
                int index;
                if (input == "object") {
                    //check if there's more than 0 object
                    if (objectsArray.size() == 0) {
                        std::cout << "No object to remove.\n";
                        goto WIZ_START;
                    }

                    //relist objects
                    listObjects(&objectsNameArray, &objectsTypeArray);

                    //check valid ID
                    while (true) {
                        std::cout << "Input ID of object to remove (default 0) ";
                        index = getInt(0);
                        if (index > (int) objectsNameArray.size() - 1) {
                            std::cout << "ID out of bound.\n";
                        }
                        else {
                            goto OBJ_REMOVE_START;
                        }
                    }

                    //remove object by index
                    OBJ_REMOVE_START:
                    objectsNameArray.erase(objectsNameArray.begin() + index);
                    objectsTypeArray.erase(objectsTypeArray.begin() + index);
                    std::cout << "Object removed\n";
                    goto WIZ_START;
                } else if (input == "material") {
                    //check if there's more than 1 material
                    if (materialsArray.size() <= 1) {
                        std::cout << "No material to remove.\n";
                        goto WIZ_START;
                    }

                    //relist materials
                    listMaterials(&materialsNameArray);

                    //check valid ID
                    while (true) {
                        std::cout << "Input ID of material to remove (default 1) ";
                        index = getInt(1);

                        if (index == 0) {
                            std::cout << "Default material cannot be removed.\n";
                        } else if (index > (int) materialsNameArray.size() - 1) {
                            std::cout << "ID out of bound.\n";
                        } else {
                            goto MATE_REMOVE_START;
                        }
                    }

                    //remove material by index
                    MATE_REMOVE_START:
                    materialsNameArray.erase(materialsNameArray.begin() + index);
                    std::cout << "Material removed\n";
                    goto WIZ_START;
                } else if (input == "matrix") {
                    //check if there's more than 1 matrix
                    if (matricesArray.size() <= 1) {
                        std::cout << "No matrix to remove.\n";
                        goto WIZ_START;
                    }

                    //relist matrices
                    listMatrices(&matricesNameArray, &matricesTypeArray);

                    //check valid ID
                    while (true) {
                        std::cout << "Input ID of matrix to remove (default 1) ";
                        index = getInt(1);

                        if (index == 0) {
                            std::cout << "Default material cannot be removed.\n";
                        } else if (index > (int) materialsNameArray.size() - 1) {
                            std::cout << "ID out of bound.\n";
                        } else {
                            goto MATRIX_REMOVE_START;
                        }
                    }

                    //remove material by index
                    MATRIX_REMOVE_START:
                    matricesNameArray.erase(matricesNameArray.begin() + index);
                    matricesTypeArray.erase(matricesTypeArray.begin() + index);
                    std::cout << "Matrix removed\n";
                    goto WIZ_START;
                } else if (input == "light") {
                    //check if there's more than 0 lights
                    if (lightsArray.size() == 0) {
                        std::cout << "No lights to remove.\n";
                        goto WIZ_START;
                    }

                    //relist lights
                    listObjects(&lightsNameArray, &lightsTypeArray);

                    //check valid ID
                    while (true) {
                        std::cout << "Input ID of light to remove (default 0) ";
                        index = getInt(0);

                        if (index > (int) lightsArray.size() - 1) {
                            std::cout << "ID out of bound";
                        } else {break;}
                    }

                    //remove light by index
                    lightsNameArray.erase(lightsNameArray.begin() + index);
                    lightsTypeArray.erase(lightsTypeArray.begin() + index);
                    std::cout << "Light removed\n";
                    goto WIZ_START;
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
            listObjects(&objectsNameArray, &objectsTypeArray);
            std::cout << "---------------------------\n";
            listObjects(&lightsNameArray, &lightsTypeArray);
            std::cout << "---------------------------\n";
            listMaterials(&materialsNameArray);
            std::cout << "---------------------------\n";
            listMatrices(&matricesNameArray, &matricesTypeArray);
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

//prompts the user for matrix stuffs
//returns a pointer to the corresponding matrix
std::shared_ptr<Matrix> makeMatrix(std::string matrixType) {
    std::shared_ptr<Matrix> newMatrix = std::make_shared<Matrix>(4);
    if (matrixType == "Translation") {
        std::cout << "(3) Input translation (default: 0 0 0) ";
        std::vector<double> trans_xyz = getDoubleList(3, std::vector<double> {0, 0, 0});
        *newMatrix = Matrix::Translation(trans_xyz[0], trans_xyz[1], trans_xyz[2]);
    } else if (matrixType == "Scaling") {
        std::cout << "(3) Input scaling factor (default: 1 1 1) ";
        std::vector<double> scale_xyz = getDoubleList(3, std::vector<double> {1, 1, 1});
        *newMatrix = Matrix::Translation(scale_xyz[0], scale_xyz[1], scale_xyz[2]);
    } else if (matrixType == "Rotation") {
        std::string input;
        while (true) {
            std::cout << "Input axis of rotation (x/y/z) ";
            std::getline(std::cin, input);
            if ((input != "x") and (input != "y") and (input != "z")) {
                std::cout << "Bad input.\n";
            } else {break;}
        }
        std::cout << "Input degree of rotation in DEG (default 0) ";
        *newMatrix = Matrix::Rotation(input[0], getInt(0));

    } else {
        std::cout << "Returning an identity matrix.\n";
        *newMatrix = Matrix::Identity();
    }

    return newMatrix;
}

void listObjects(std::vector<std::string>* objectsNameArray, std::vector<std::string>* objectsTypeArray) {
    std::cout << "ID   Objects        Name\n";
    for (size_t i = 0; i < objectsNameArray -> size(); i++) {
        std::cout << std::setw(5) << std::left << i
                  << std::setw(15) << std::left << objectsTypeArray -> at(i)
                  << objectsNameArray -> at(i) << std::endl;
    }
}

void listMaterials(std::vector<std::string>* materialsNameArray) {
    std::cout << "ID   Material Name\n";
    for (size_t i = 0; i < materialsNameArray -> size(); i++) {
        std::cout << std::setw(5) << std::left << i
                  << std::setw(15) << std::left << materialsNameArray -> at(i)
                  << std::endl;
    }
}

void listMatrices(std::vector<std::string>* matricesNameArray, std::vector<std::string>* matricesTypeArray) {
    std::cout << "ID   Matrix         Name\n";
    for (size_t i = 0; i < matricesNameArray -> size(); i++) {
        std::cout << std::setw(5) << std::left << i
                  << std::setw(15) << std::left << matricesTypeArray -> at(i)
                  << matricesNameArray -> at(i) << std::endl;
    }
}
