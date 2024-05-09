#include <iostream>
#include "matrix/matrix.h"

using namespace std;

int main() {
    Matrix A = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
    };

    cout << A.determinant() << endl;

    return 0;
}