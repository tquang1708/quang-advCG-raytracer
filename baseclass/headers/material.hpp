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
    public:
        Material();

        //getter funcs
        Color getColor() const;
        double getDiffuse() const;
        double getAmbient() const;
        double getShininess() const;

        //setter funcs
        void setColor(Color c);
        void setDiffuse(double d);
        void setAmbient(double a);
        void setShininess(double s);
        //operator overloading
        bool operator== (const Material &m) const;
};

#endif
