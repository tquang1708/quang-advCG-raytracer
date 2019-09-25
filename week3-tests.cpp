#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "baseclass/baseclass_headers.hpp"

TEST_CASE("Constructing and inspecting a 4x4 matrix") {
    Matrix M(4);
    double valArray[16] = {1, 2, 3, 4,
                           5.5, 6.5, 7.5, 8.5,
                           9, 10, 11, 12,
                           0, 0, 0, 1};
    M.fillMatrix(valArray);
    REQUIRE(M.accessMatrix(0, 0) == 1);
    REQUIRE(M.accessMatrix(0, 3) == 4);
    REQUIRE(M.accessMatrix(1, 0) == 5.5);
    REQUIRE(M.accessMatrix(1, 2) == 7.5);
    REQUIRE(M.accessMatrix(2, 2) == 11);
    REQUIRE(M.accessMatrix(3, 0) == 0);
    REQUIRE(M.accessMatrix(3, 3) == 1);
}

TEST_CASE("A 2x2 matrix ought to be representable") {
    Matrix M(2);
    double valArray[4] = {-3, 5,
                          1, -2};
    M.fillMatrix(valArray);
    REQUIRE(M.accessMatrix(0, 0) == -3);
    REQUIRE(M.accessMatrix(0, 1) == 5);
    REQUIRE(M.accessMatrix(1, 0) == 1);
    REQUIRE(M.accessMatrix(1, 1) == -2);
}

TEST_CASE("A 3x3 matrix ought to be representable") {
    Matrix M(3);
    double valArray[9] = {-3, 5, 0,
                          1, -2, -7,
                          0, 1, 1};
    M.fillMatrix(valArray);
    REQUIRE(M.accessMatrix(0, 0) == -3);
    REQUIRE(M.accessMatrix(1, 1) == -2);
    REQUIRE(M.accessMatrix(2, 2) == 1);
}

TEST_CASE("Matrix equality with identical matrices") {
    Matrix A(4);
    Matrix B(4);
    double valA[16] = {1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       0, 0, 0, 1};
    double valB[16] = {1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       0, 0, 0, 1};
    A.fillMatrix(valA);
    B.fillMatrix(valB);
    REQUIRE(A == B);
}

TEST_CASE("Matrix equality with different matrices") {
    Matrix A(4);
    Matrix B(4);
    double valA[16] = {1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       0, 0, 0, 1};
    double valB[16] = {2, 3, 4, 5,
                       6, 7, 8, 9,
                       8, 7, 6, 5,
                       0, 0, 0, 1};
    A.fillMatrix(valA);
    B.fillMatrix(valB);
    REQUIRE(A != B);
}

TEST_CASE("Multiplying two matrices") {
    Matrix A(4);
    Matrix B(4);
    Matrix AB(4);
    double valA[16] = {1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       0, 0, 0, 1};
    double valB[16] = {-2, 1, 2, 3,
                       3, 2, 1, -1,
                       4, 3, 6, 5,
                       0, 0, 0, 1};
    double valAB[16] = {16, 14, 22, 20,
                       36, 38, 58, 52,
                       34, 46, 68, 60,
                       0, 0, 0, 1};
    A.fillMatrix(valA);
    B.fillMatrix(valB);
    AB.fillMatrix(valAB);
    REQUIRE(A * B == AB);
}

TEST_CASE("A matrix multiplied by a tuple") {
    Matrix A(4);
    Tuple b(1, 2, 3, 1);
    Tuple Ab(18, 24, 33, 1);
    double valA[16] = {1, 2, 3, 4,
                       2, 4, 4, 2,
                       8, 6, 4, 1,
                       0, 0, 0, 1};
    A.fillMatrix(valA);
    REQUIRE(A * b == Ab);
}

TEST_CASE("Multiplying a matrix by the identity matrix") {
    Matrix A(4);
    Matrix ident(4);
    double valA[16] = {0, 1, 2, 4,
                       1, 2, 4, 8,
                       2, 4, 8, 16,
                       0, 0, 0, 1};
    double val_ident[16] = {1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1};
    A.fillMatrix(valA);
    ident.fillMatrix(val_ident);
    REQUIRE(A * ident == A);
}

TEST_CASE("Multiplying the identity matrix by a tuple") {
    Tuple b(1, 2, 3, 4);
    Matrix ident(4);
    double val_ident[16] = {1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1};
    ident.fillMatrix(val_ident);
    REQUIRE(ident * b == b);
}

TEST_CASE("Calculating the determinant of a 2x2 matrix") {
    Matrix A(2);
    double valA[4] = {1, 5,
                      -3, 2};
    A.fillMatrix(valA);
    REQUIRE(A.determinant() == 17);
}

TEST_CASE("A submatrix of a 3x3 matrix is a 2x2 matrix") {
    Matrix A(3);
    double valA[9] = {1, 5, 0,
                      -3, 2, 7,
                      0, 6, -3};
    A.fillMatrix(valA);
    Matrix subA(2);
    double valSubA[4] = {-3, 2,
                         0, 6};
    subA.fillMatrix(valSubA);
    REQUIRE(A.submatrix(0, 2) == subA);
}

TEST_CASE("Calculating a cofactor of a 3x3 matrix") {
    Matrix A(3);
    double valA[9] = {3, 5, 0,
                      2, -1, -7,
                      6, -1, 5};
    A.fillMatrix(valA);
    REQUIRE(A.cofactor(0, 0) == -12);
    REQUIRE(A.cofactor(1, 0) == -25);
}

TEST_CASE("Calculating the determinant of a 3x3 matrix") {
    Matrix A(3);
    double valA[9] = {1, 2, 6,
                      -5, 8, -4,
                      2, 6, 4};
    A.fillMatrix(valA);
    REQUIRE(A.cofactor(0, 0) == 56);
    REQUIRE(A.cofactor(0, 1) == 12);
    REQUIRE(A.cofactor(0, 2) == -46);
    REQUIRE(A.determinant() == -196);
}

TEST_CASE("Calculating the determinant of a 4x4 matrix") {
    Matrix A(4);
    double valA[16] = {-2, -8, 3, 5,
                   -3, 1, 7, 3,
                   1, 2, -9, 6,
                   0, 0, 0, 1};
    A.fillMatrix(valA);
    REQUIRE(A.determinant() == 185);
}

TEST_CASE("Testing an invertible matrix for invertibility") {
    Matrix A(4);
    double valA[16] = {6, 4, 4, 4,
                       5, 5, 7, 6,
                       4, -9, 3, -7,
                       0, 0, 0, 1};
    A.fillMatrix(valA);
    REQUIRE(A.determinant() == 260);
}

TEST_CASE("Testing a noninvertible matrix for invertibility") {
    Matrix A(4);
    double valA[16] = {-4, 2, 0, -3,
                       9, 6, 0, 6,
                       0, -5, 0, -5,
                       0, 0, 0, 1};
    A.fillMatrix(valA);
    REQUIRE(A.determinant() == 0);
    REQUIRE(A.inverse() == NULL);
}

TEST_CASE("Calculating the inverse of a matrix") {
    Matrix A(4);
    double valA[16] = {-5, 2, 6, -8,
                       1, -5, 1, 8,
                       7, 7, -6, -7,
                       0, 0, 0, 1};
    A.fillMatrix(valA);
    Matrix B(4);
    double valB[16] = {0.14110, 0.33129, 0.19632, -0.14724,
                       0.07975, -0.07362, 0.06748, 1.69939,
                       0.25767, 0.30061, 0.14110, 0.64417,
                       0.0, 0.0, 0.0, 1.0};
    B.fillMatrix(valB);
    REQUIRE(A.inverse() == B);
}

TEST_CASE("Multiplying a product by its inverse") {
    Matrix A(4);
    Matrix B(4);
    Matrix C(4);
    double valA[16] = {3, -9, 7, 3,
                       3, -8, 2, -9,
                       -4, 4, 4, 1,
                       0, 0, 0, 1};
    double valB[16] = {8, 2, 2, 2,
                       3, -1, 7, 0,
                       7, 0, 5, 4,
                       0, 0, 0, 1};
    A.fillMatrix(valA);
    B.fillMatrix(valB);
    C = A * B;
    REQUIRE(C * B.inverse() == A);
}
