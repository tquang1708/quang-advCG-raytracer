/* camera.cpp - implementations of camera.hpp funcs
 * Quang Tran - 10/16/19
 * */

#include "headers/camera.hpp"
#include <math.h>

Camera::Camera(int h, int v, int f): hsize(h), vsize(v), fov(f) {
    transform = Matrix::Identity();
}

//getter funcs
int Camera::getHSize() const {
    return hsize;
}

int Camera::getVSize() const {
    return vsize;
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

Ray Camera::cameraRay(double x, double y) {
    this -> pixelSize();
    double xoffset = (x + 0.5) * pixelS;
    double yoffset = (y + 0.5) * pixelS;

    double worldX = halfW - xoffset;
    double worldY = halfH - yoffset;

    //canvas at z = -1
    Tuple pixel = transform.inverse() * Tuple::Point(worldX, worldY, -1);
    Tuple origin = transform.inverse() * Tuple::Point(0, 0, 0);
    Tuple direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}

void Camera::render(World w, std::string filename) {
    Canvas image(hsize, vsize);

    for (double y = 0; y < vsize; y++) {
        for (double x = 0; x < hsize; x++) {
            Ray r = this -> cameraRay(x, y);
            Color c = w.colorAt(r);
            image.write_pixel(x, y, c);
        }
    }

    image.toPPM(filename);
}
