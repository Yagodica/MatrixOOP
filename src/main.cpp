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
    };


    Matrix C = A + B;
    cout << C << endl;

    return 0;
}