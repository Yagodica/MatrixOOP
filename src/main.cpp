#include <iostream>
#include "matrix/matrix.h"

using namespace std;

int main() {
    Matrix B(2, 3);
    Matrix A(3, 1);

    A[0][0] = 1;
    A[1][0] = 2;
    A[2][0] = 3;

    B[0][0] = 1; B[0][1] = 2; B[0][2] = 0;
    B[1][0] = 3; B[1][1] = 1; B[1][2] = -1;

    cout << A*B << endl;

    return 0;
}