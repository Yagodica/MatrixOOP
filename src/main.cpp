#include <iostream>
#include "matrix/matrix.h"

using namespace std;

int main() {
    Matrix A = {{1, 2}, {3, 4}, {5, 6}};
    Matrix B = {{7, 8}, {9, 0}};
    Matrix C = B+A;

    cout << C << endl;


    return 0;
}