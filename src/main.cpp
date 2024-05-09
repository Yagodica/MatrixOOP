#include <iostream>
#include "matrix/matrix.h"

using namespace std;

int main() {
    Matrix A = {
            {2, 5, 7},
            {6, 3, 4},
            {5, -2, -3}
    };

    Matrix B = {
            {-1, 1},
            {1, 2},
            {1, 2},
    };

    B[1][1] = 4;

    Matrix I = Matrix::createIdentity(3);
    Matrix AI = Matrix::augment(A, I);


    cout << AI << endl;

    return 0;
}