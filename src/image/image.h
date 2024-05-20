#ifndef MATRIXOOP_IMAGE_H
#define MATRIXOOP_IMAGE_H

#include "matrix.h"
#include <cstdint>

class Image : public Matrix {
public:
    static Matrix gaussianBlur(Matrix &image, double sigma, int ksize);
    static Matrix readMatrixFromPGMFile(const std::string &filename);
    static void saveMatrixToPGMFile(Matrix &matrix, const std::string &filename);

    void setSigma(double s) { sigma = s; }
    void setKsize(int k) { ksize = k; }

private:
    double sigma = 1.0;
    int ksize = 1;

};

#endif