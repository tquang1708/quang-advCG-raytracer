/* camera.hpp - header file for the camera
 * Quang Tran - 10/16/19
 * */

#pragma once

#include "matrix.hpp"
#include "ray.hpp"
#include "canvas.hpp"
#include "world.hpp"

#include <string>

class Camera {
    private:
        int hsize;
        int vsize;
        double fov;
        double apertureRadius;
        double focal;
        Matrix transform;

        double halfW;
        double halfH;
        double pixelS;
        
    public:
        bool aaOn;
        int aaSamples;
        int aperSamples;

        Camera(int, int, double, double, double, int, int);

        //getter funcs
        int getHSize() const;
        int getVSize() const;
        double getApertureRadius() const;
        double getFocal() const;
        double getFOV() const;
        Matrix getTransform() const;

        //setter funcs
        void setHSize(int);
        void setVSize(int);
        void setApertureRadius(double);
        void setFocal(double);
        void setFOV(double);
        void setTransform(Matrix);

        //camera funcs
        double pixelSize();
        //Ray cameraRay(double, double);
        Color cameraAperture(World w, double, double);
        void render(World, std::string);
        Color antiAliasing(World w, double x, double y);
};
