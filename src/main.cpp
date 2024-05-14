#include <iostream>
#include "matrix/matrix.h"

using namespace std;

int main() {

//    Matrix A = {
//            {1, 2, 3},
//            {4, 5, 6},
//            {7, 8, 9},
//            };
//
//    Matrix B = {
//            {2, 5, 7},
//            {6, 3, 4},
//            {5, -2, -3},
//            };

    Matrix A = {
            {2, 1, 1},
            {1, -1, 0},
            {3, -1, 2},
            };


    Matrix Ax = {
            {2},
            {-2},
            {2},
            };

    Matrix C = Matrix::solve(A, Ax);

    cout << C << endl;


    return 0;
}