/* material.hpp - header file for material object
 * Quang Tran - 9/14/19
 * */

#pragma once

#include "color.hpp"
#include "tuple.hpp"
#include "pattern.hpp"
#include <memory>

class Material {
    private:
        Color color;
        std::shared_ptr<Pattern> pattern;
        double ambient;
        double diffuse;
        double shininess;
        double specular;
        double emission;
        double reflectivity;
        double transparency;
        double refractive_index;
        bool shadow_cast;
    public:
        Material();

        //getter funcs
        Color getColor() const;
        std::shared_ptr<Pattern> getPattern() const;
        double getDiffuse() const;
        double getAmbient() const;
        double getShininess() const;
        double getSpecular() const;
        double getReflectivity() const;
        double getEmission() const;
        double getTransparency() const;
        double getRefractiveIndex() const;
        bool getShadowCast() const;

        //setter funcs
        Material setColor(Color c);
        Material setPattern(std::shared_ptr<Pattern> p);
        Material setDiffuse(double d);
        Material setAmbient(double a);
        Material setShininess(double s);
        Material setSpecular(double s);
        Material setReflectivity(double);
        Material setEmission(double);
        Material setTransparency(double);
        Material setRefractiveIndex(double);
        Material setShadowCast(bool);

        //operator overloading
        bool operator== (const Material &m) const;
};
