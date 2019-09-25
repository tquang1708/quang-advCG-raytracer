/* Implementations of functions of matrix classes
 * Quang Tran - 9/24/2019
 * */

#include "headers/matrix.hpp"
#include <vector>

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

bool Matrix::operator==(const Matrix &m) const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix_grid[i][j] != m.accessMatrix(i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &m) const {
    return !(*this == m);
}
