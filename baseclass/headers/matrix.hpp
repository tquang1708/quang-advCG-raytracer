/* matrix.hpp - Header file for matrix class
 * Quang Tran - 9/24/2019
 * */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include "tuple.hpp"

class Matrix {
    private:
        int size;
        int detCalc = 0;
        double det;
        std::vector<std::vector<double>> matrix_grid;
    public:
        //constructors
        Matrix(int size_);

        //filler
        void fillMatrix(double* valArray);

        //accesser
        double accessMatrix(int row, int col) const;
        int getSize() const;

        //operator == overload
        bool operator== (const Matrix &m) const;
        bool operator!= (const Matrix &m) const;

        //operator * overload
        Matrix operator* (const Matrix &m) const;
        Tuple operator* (const Tuple &t) const;
        
        //calculation function
        double determinant();
        Matrix submatrix(int row, int col) const;
        double cofactor(int row, int col) const;

        //helper function
        double multMatRowTuple(const std::vector<double> matRow, const Tuple &t) const;
};

#endif
