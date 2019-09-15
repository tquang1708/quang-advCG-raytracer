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
        int diffuse;
    public:
        Material();

        //getter funcs
        Color getColor() const;
        int getDiffuse() const;

        //setter funcs
        void setColor(Color c);

        //operator overloading
        bool operator== (const Material &m) const;
};

#endif
