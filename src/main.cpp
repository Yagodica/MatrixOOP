#include <iostream>
#include "matrix/matrix.h"

int main() {
    Matrix A(3, 3);  // creates a 3x3 matrix initialized to 0
    Matrix B(3, 3);  // creates a 3x3 matrix initialized to 0

    Matrix F = Matrix::createIdentity(3);

    B(0, 0) = 9; B(0, 1) = 8; B(0, 2) = 7;
    B(1, 0) = 6; B(1, 1) = 5; B(1, 2) = 4;
    B(2, 0) = 3; B(2, 1) = 2; B(2, 2) = 1;

    Matrix C = B + F;
    std::cout << C << std::endl;

    return 0;
}