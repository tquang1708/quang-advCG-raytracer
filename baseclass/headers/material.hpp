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
        double diffuse;
    public:
        Material();

        //getter funcs
        Color getColor() const;
        double getDiffuse() const;

        //setter funcs
        void setColor(Color c);
        void setDiffuse(double d);

        //operator overloading
        bool operator== (const Material &m) const;
};

#endif
