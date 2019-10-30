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
        double reflectivity;
        double emission;
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

        //setter funcs
        void setColor(Color c);
        void setDiffuse(double d);
        void setAmbient(double a);
        void setShininess(double s);
        void setSpecular(double s);
        void setReflectivity(double);
        void setEmission(double);

        //operator overloading
        bool operator== (const Material &m) const;
};

#endif
