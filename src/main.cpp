#include <iostream>
#include "matrix/matrix.h"
#include <chrono>

using namespace std;

int main() {
    Matrix A = Matrix::randomMatrix(1000, 1000, 0, 9);
    Matrix B = Matrix::randomMatrix(1000, 1000, 0, 9);

    auto begin = std::chrono::steady_clock::now();

    Matrix C = A + B;

    auto end = std::chrono::steady_clock::now();

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";

    return 0;
}