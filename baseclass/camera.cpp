/* camera.cpp - implementations of camera.hpp funcs
 * Quang Tran - 10/16/19
 * */

#include "headers/camera.hpp"
#include <math.h>
#include <chrono>
#include <random>

#include <iostream>
#include <omp.h>
#define NUM_THREADS 6


Camera::Camera(int h, int v, double f, double a, double foc): hsize(h), vsize(v), fov(f), apertureRadius(a), focal(foc) {
    transform = Matrix::Identity();
}

//getter funcs
int Camera::getHSize() const {
    return hsize;
}

int Camera::getVSize() const {
    return vsize;
}

double Camera::getFocal() const {
    return focal;
}

double Camera::getApertureRadius() const {
    return apertureRadius;
}

double Camera::getFOV() const {
    return fov;
}

Matrix Camera::getTransform() const {
    return transform;
}

//setter funcs
void Camera::setHSize(int h) {
    hsize = h;
}

void Camera::setVSize(int v) {
    vsize = v;
}

void Camera::setFOV(double f) {
    fov = f;
}

void Camera::setFocal(double f) {
    focal = f;
}

void Camera::setApertureRadius(double r) {
    apertureRadius = r;
}

void Camera::setTransform(Matrix m) {
    transform = m;
}

//camera funcs
double Camera::pixelSize() {
    //convert to rad
    double fovRad = fov * M_PI / 180.0;

    double halfView = tan(fovRad / 2);
    double aspect = (double) hsize / (double) vsize;

    if (aspect >= 1) {
        halfW = halfView;
        halfH = halfView / aspect;
    }
    else {
        halfW = halfView * aspect;
        halfH = halfView;
    }

    pixelS = (halfW * 2) / hsize;
    return pixelS;
}

/*Ray Camera::cameraRay(double x, double y) {
    this -> pixelSize();
    double xoffset = (x + 0.5) * pixelS;
    double yoffset = (y + 0.5) * pixelS;

    double worldX = halfW - xoffset;
    double worldY = halfH - yoffset;

    //canvas at z = -1
    Tuple pixel = transform.inverse() * Tuple::Point(worldX, worldY, focal);
    Tuple origin = transform.inverse() * Tuple::Point(0, 0, 0);
    Tuple direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}*/

Color Camera::cameraAperture(World w, double x, double y) {
    this -> pixelSize();
    double xoffset = (x + 0.5) * pixelS;
    double yoffset = (y + 0.5) * pixelS;

    double worldX = halfW - xoffset;
    double worldY = halfH - yoffset;

    //pixel that the ray is meant to calculate
    Tuple pixel = transform.inverse() * Tuple::Point(worldX, worldY, focal);
    Color out(0, 0, 0);

    //basic 1 ray
    if (apertureRadius == 0) {
        Tuple origin = transform.inverse() * Tuple::Point(0, 0, 0);
        Tuple direction = (pixel - origin).normalize();
        Ray r(origin, direction);

        out += w.colorAt(r, 5);
    } else {
        //rng
        int seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);
        std::uniform_real_distribution<double> dis(-apertureRadius/4, apertureRadius/4);

        //std::vector<std::vector<double>> offset_matrix = {{-0.25, 0.75}, {0.25, 0.75}, {-0.5, 0.5}, {0.5, 0.5},
        //                                                  {-0.75, 0.25}, {-0.25, 0.25}, {0.25, 0.25}, {0.75, 0.25},
        //                                                  {-0.75, -0.25}, {-0.25, -0.25}, {0.25, -0.25}, {0.75, -0.25},
        //                                                  {-0.25, -0.75}, {0.25, -0.75}, {-0.5, -0.5}, {0.5, -0.5}};
        std::vector<std::vector<double>> offset_matrix = {{-0.5, 0.5}, {0.5, 0.5}, {-0.5, -0.5}, {0.5, -0.5}};

        //loop calculating origin then adding up color
        //calculating x and y in four quadrants of the aperture
        for (int offset = 0; offset < (int) offset_matrix.size(); offset++) {
            /*double rayX = x_gen(generator) * subX;
            std::uniform_real_distribution<double> y_gen(0, sqrt(apertureRadius - rayX * rayX));
            double rayY = y_gen(generator) * subY;*/
            double rayX = apertureRadius * offset_matrix[offset][0] + dis(generator);
            double rayY = apertureRadius * offset_matrix[offset][1] + dis(generator);

            Tuple origin = transform.inverse() * Tuple::Point(rayX, rayY, 0);
            Tuple direction = (pixel - origin).normalize();
            Ray r(origin, direction);

            out += w.colorAt(r, 5);
        }

        out = out * (1.0 / offset_matrix.size());
    }

    return out;
}

void Camera::render(World w, std::string filename) {
    double start_time, run_time;
    start_time = omp_get_wtime();

    Canvas image(hsize, vsize);

    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int numthreads = omp_get_num_threads();
        for (double y = id; y < vsize; y = y + numthreads) {
            for (double x = 0; x < hsize; x++) {
                Color c;
                if (aaOn) {
                    c = antiAliasing(w, x, y);
                } else {
                    c = this -> cameraAperture(w, x, y);
                }
                image.write_pixel(x, y, c);
            }
        }
    }

    image.toPPM(filename);

    run_time = omp_get_wtime() - start_time;
    std::cout << "Runtime: " << run_time << std::endl;
}

//antialiasing attempt
//jittered sampling
Color Camera::antiAliasing(World w, double x, double y) {
    Color out(0, 0, 0);

    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> dis(-0.15, 0.15);

    //4 random rays in 4 subspixels
    for (int subX = 0; subX < 2; subX++) {
        for (int subY = 0; subY < 2; subY++) {
            double rayX = x - 0.25 + subX * 0.5 + dis(generator);
            double rayY = y - 0.25 + subY * 0.5 + dis(generator);
            Color c = this -> cameraAperture(w, rayX, rayY);
            out = out + c;
        }
    }

    out = out * 0.25;

    return out;
}
