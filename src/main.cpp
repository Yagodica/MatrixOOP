#include <iostream>
#include "matrix/matrix.h"
//#include "GrayscaleImage/GrayscaleImage.h"
//#include "BMP.h"



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

    Matrix C = A / B;

    cout << C << endl;


//    BmpImage image;
//
//    if (image.read("sample_5184×3456.bmp")) {
//        image.write("output.bmp");
//    }

    return 0;
}