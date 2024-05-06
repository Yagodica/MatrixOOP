#include <iostream>
#include "matrix/matrix.h"

int main() {
    Matrix A(3, 3);  // creates a 3x3 matrix initialized to 0
    Matrix B(3, 3);  // creates a 3x3 matrix initialized to 0

    // initialize the matrices with some values
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

    B(0, 0) = 9; B(0, 1) = 8; B(0, 2) = 7;
    B(1, 0) = 6; B(1, 1) = 5; B(1, 2) = 4;
    B(2, 0) = 3; B(2, 1) = 2; B(2, 2) = 1;

    Matrix C = A * B;
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;

    return 0;
}