#include <iostream>
#include "matrix/matrix.h"

using namespace std;

int main() {
    Matrix A = {
            {1, 2},
            {2, -1},
            {3, 0}
    };

    Matrix B = {
            {-1, 1},
            {1, 2},
            {1, 2},
    };

    B[1][1] = 4;

    Matrix C = A / 1;
    cout << C << endl;

    return 0;
}