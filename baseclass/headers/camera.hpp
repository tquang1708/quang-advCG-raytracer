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
        Matrix transform;

        double halfW;
        double halfH;
        double pixelS;
        
    public:
        bool aaOn;

        Camera(int, int, double);

        //getter funcs
        int getHSize() const;
        int getVSize() const;
        double getFOV() const;
        Matrix getTransform() const;

        //setter funcs
        void setHSize(int);
        void setVSize(int);
        void setFOV(double);
        void setTransform(Matrix);

        //camera funcs
        double pixelSize();
        Ray cameraRay(double, double);
        void render(World, std::string);
        Color antiAliasing(World w, double x, double y);
};
