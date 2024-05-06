#include <iostream>
#include "matrix/matrix.h"

int main() {
//    for (int i = 0; )
    Matrix m(3, 3);
    Matrix s(1, 2);
    std::cout << (m *= s) << std::endl;
    return 0;
}