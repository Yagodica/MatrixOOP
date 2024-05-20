#include <iostream>
#include <fstream>
#include <string>
#include "matrix/matrix.h"
#include "image/image.h"
#include <chrono>

using namespace std;

int main() {
    try {
        // Read the image from a PGM file

        Matrix image = Image::readMatrixFromPGMFile("input.pgm");

        // Perform a Gaussian blur on the image
        double sigma = 2.0;
        int ksize = 1;
        Matrix blurredImage = Image::gaussianBlur(image, sigma, ksize);

        // Save the result to a new PGM file
        Image::saveMatrixToPGMFile(blurredImage, "output.pgm");

        std::cout << "Gaussian blur successfully applied to the image and saved to output.pgm" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
