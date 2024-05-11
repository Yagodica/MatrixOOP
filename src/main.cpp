#include <iostream>
#include "matrix/matrix.h"
#include "GrayscaleImage/GrayscaleImage.h"

using namespace std;

int main() {
    Matrix A = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
    };

    Matrix B = {
            {2, 5, 7},
            {6, 3, 4},
            {5, -2, -3},
    };

//    matrix C = (A / B);
    Matrix C = A^4;

    cout << C << endl;

    return 0;
}