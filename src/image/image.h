#ifndef MATRIXOOP_IMAGE_H
#define MATRIXOOP_IMAGE_H

#include "matrix.h"
#include <cstdint>

class Image : public Matrix {
public:
    Image(double sigma, int ksize, const std::string& filename) : sigma(sigma), ksize(ksize) {
        image = readMatrixFromPGMFile(filename);
    }

    void applyGaussianBlur() {
        image = gaussianBlur(image, sigma, ksize);
    }

    void saveToPGMFile(const std::string& filename) {
        saveMatrixToPGMFile(image, filename);
    }

    void setSigma(double s) { sigma = s; }
    void setKsize(int k) { ksize = k; }

private:
    double sigma = 1.0;
    int ksize = 1;

    Matrix image;

    static Matrix gaussianBlur(Matrix &image, double sigma, int ksize);
    static Matrix readMatrixFromPGMFile(const std::string &filename);
    static void saveMatrixToPGMFile(Matrix &matrix, const std::string &filename);
};

#endif