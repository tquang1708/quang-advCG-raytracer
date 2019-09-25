/* matrix.hpp - Header file for matrix class
 * Quang Tran - 9/24/2019
 * */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

class Matrix {
    private:
        int size;
        std::vector<std::vector<double>> matrix_grid;
    public:
        //constructors
        Matrix(int size_);

        //filler
        void fillMatrix(double* valArray);

        //accesser
        double accessMatrix(int row, int col) const;

        //operator == overload
        bool operator== (const Matrix &m) const;
        bool operator!= (const Matrix &m) const;
};

#endif
