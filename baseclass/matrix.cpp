/* Implementations of functions of matrix classes
 * Quang Tran - 9/24/2019
 * */

#include "headers/matrix.hpp"
#include <vector>
#include <iostream>
#include "headers/tuple.hpp"

//default constructor defaults to 4
Matrix::Matrix() {
    Matrix(4);
}

Matrix::Matrix(int s): size(s) {
    //initialize the matrix with all 0s
    matrix_grid.resize(s, std::vector<double>(s, 0));
}

void Matrix::fillMatrix(double* valArray) {
    //fill matrix with values in valArray row by row
    int arrayIndex = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix_grid[i][j] = valArray[arrayIndex];
            ++arrayIndex;
        }
    }
}

double Matrix::accessMatrix(int row, int col) const {
    return matrix_grid[row][col];
}

int Matrix::getSize() const {
    return size;
}

bool Matrix::operator==(const Matrix &m) const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if ((matrix_grid[i][j] - m.accessMatrix(i, j)) > EPSILON) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &m) const {
    return !(*this == m);
}

Matrix Matrix::operator* (const Matrix &m) const {
    if (size != m.getSize()) {
        return NULL;
    }
    Matrix out(size);
    double val_out[size * size];

    //initializing array with 0
    for (int i = 0; i < size * size; i++) {
        val_out[i] = 0;
    }

    //filling value array
    int arrayIndex = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                val_out[arrayIndex] += matrix_grid[i][k] * m.accessMatrix(k, j);
            }
            ++arrayIndex;
        }
    }
    out.fillMatrix(val_out);
    return out;
}

Tuple Matrix::operator* (const Tuple &t) const {
    //all tuple has size 4
    if (size != 4) {
        return Tuple(0, 0, 0, 0);
    }

    double val_out[4] = {0};

    //filling value array
    for (int i = 0; i < 4; i++) {
        val_out[i] = multMatRowTuple(matrix_grid[i], t);
    }
    Tuple out(val_out[0], val_out[1], val_out[2], val_out[3]);

    return out;
}

Matrix Matrix::operator* (const double &d) const {
    Matrix out(size);
    double val_out[size * size];
    int arrayIndex = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            val_out[arrayIndex] = matrix_grid[i][j] * d;
            arrayIndex++;
        }
    }
    out.fillMatrix(val_out);
    return out;
}

//determinant stuffs
double Matrix::determinant() {
    if (detCalc == 1) {
        return det;
    }
    else if (size == 2) {
        det = matrix_grid[0][0] * matrix_grid[1][1] -
               matrix_grid[0][1] * matrix_grid[1][0];
        detCalc = 1;
        return det;
    }
    else if (size == 4) {
        det = submatrix(3, 3).determinant();
        detCalc = 1;
        return det;
    }
    else if (size == 3) {
        det = matrix_grid[0][0]*cofactor(0, 0) +
               matrix_grid[0][1]*cofactor(0, 1) +
               matrix_grid[0][2]*cofactor(0, 2);
        detCalc = 1;
        return det;
    }
    return 0;
}

Matrix Matrix::submatrix(int row, int col) const{
    Matrix out(size - 1);
    double valOut[(size - 1) * (size - 1)];

    //initializing array vals
    for (int i = 0; i < (size - 1) * (size - 1); i++) {
        valOut[i] = 0;
    }

    int arrayIndex = 0;
    //populating array vals
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != row && j != col) {
                valOut[arrayIndex] = matrix_grid[i][j];
                ++arrayIndex;
            }
        }
    }

    out.fillMatrix(valOut);
    return out;
}

double Matrix::cofactor(int row, int col) const {
    double sign;
    if ((row + col) % 2 == 0) {
        sign = 1;
    }
    else {
        sign = -1;
    }
    return submatrix(row, col).determinant() * sign;
}

//inverse
Matrix Matrix::inverse() {
    determinant();
    if (det == 0) {
        return NULL;
    }
    else if (inversion != NULL) {
        return *inversion;
    }
    else {
        static Matrix out(size);
        double valOut[size * size];

        int arrayIndex = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                valOut[arrayIndex] = (1 / det) * cofactor(j, i);
                arrayIndex++;
            }
        }
        out.fillMatrix(valOut);
        inversion = &out;
        return out;
    }
}

//array mult helper func for tuples
double Matrix::multMatRowTuple(const std::vector<double> matRow, const Tuple &t) const{
    return matRow[0] * t.getx() + matRow[1] * t.gety() +
           matRow[2] * t.getz() + matRow[3] * t.getw();
}

//transpose helper function for inverse
Matrix Matrix::transpose() const {
    Matrix out(size);
    double valOut[size * size];

    int arrayIndex = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            valOut[arrayIndex] = matrix_grid[j][i];
            arrayIndex++;
        }
    }

    out.fillMatrix(valOut);
    return out;
}

