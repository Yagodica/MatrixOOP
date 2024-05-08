#include <iostream>
#include "matrix/matrix.h"

using namespace std;

int main() {
    Matrix A = {
            {1, 3, 1, 9},
            {1, 1, -1, 1},
            {3, 11, 5, 35}
    };

    Matrix B = {
            {-1, 1},
            {1, 2},
            {1, 2},
    };

    B[1][1] = 4;

//    Matrix C = Matrix::solve(A);
    cout << A << endl;

    return 0;
}