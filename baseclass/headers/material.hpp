/* material.hpp - header file for material object
 * Quang Tran - 9/14/19
 * */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "tuple.hpp"

class Material {
    private:
        Color color;
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

#endif
