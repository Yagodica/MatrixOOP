#include <iostream>
#include "matrix/matrix.h"
#include <chrono>

using namespace std;

int main() {
//    Matrix A = {
//            {2, -1, 3, -5},
//            {1, -1, -5, 0},
//            {3, -2, -2, -5},
//            {7, -5 , -9, -10}
//    };
//
//    Matrix B = {
//            {1},
//            {2},
//            {3},
//            {8}
//    };

    Matrix A = {
            {1, 1, 2, 3},
            {1, 2, 3, -1},
            {3, -1, -1, -2},
            {2, 3 , -1, -1}
    };

    Matrix B = {
            {1},
            {-4},
            {-4},
            {-6}
    };

//    Matrix A = {
//            {1, 2, 3},
//            {3, 5, 7},
//            {1, 3, 4}
//    };
//
//    Matrix B = {
//            {3},
//            {0},
//            {1}
//    };

    cout << Matrix::solve(A, B) << endl;

    return 0;
}