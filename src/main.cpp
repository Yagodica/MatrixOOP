#include <iostream>
#include "matrix/matrix.h"
#include <chrono>

using namespace std;

int main() {
    Matrix A(3, 3);
    Matrix B(3, 2);

    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(2, 0) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;

    B(0, 0) = 10; B(0, 1) = 11;
    B(1, 0) = 12; B(1, 1) = 13;
    B(2, 0) = 14; B(2, 1) = 15;

    Matrix AB = Matrix::augment(A, B);
    cout << AB;
    return 0;
}