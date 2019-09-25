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
