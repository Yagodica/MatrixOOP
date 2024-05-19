#ifndef MATRIXOOP_IMAGE_H
#define MATRIXOOP_IMAGE_H

#include "Matrix.h"
#include <cstdint>

class Image : public Matrix {
public:
    double getGaussianKernel(int kernelSize, int x, int y) {
        double sigma = 0.3 * ((kernelSize - 1) * 0.5 - 1) + 0.8;
        double sigmaSquare = sigma * sigma;
        double twoSigmaSquare = 2.0 * sigmaSquare;
        double xFactor = (x - (kernelSize - 1) * 0.5);
        double yFactor = (y - (kernelSize - 1) * 0.5);
        return (1.0 / (M_PI * twoSigmaSquare)) * std::exp(-(xFactor * xFactor + yFactor * yFactor) / twoSigmaSquare);
    }

    Image applyKernel(Image& kernel) {
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                double sum = 0.0;
                for (int m = 0; m < kernel.getRows(); ++m) {
                    for (int n = 0; n < kernel.getCols(); ++n) {
                        int ii = i + m - (kernel.getRows() - 1) / 2;
                        int jj = j + n - (kernel.getCols() - 1) / 2;
                        if (ii >= 0 && ii < rows_ && jj >= 0 && jj < cols_) {
                            sum += kernel(m, n) * (*this)(ii, jj);
                        }
                    }
                }
                result(i, j) = static_cast<uint8_t>(sum);
            }
        }
        return result;
    }

    Matrix GaussianBlur(int kernelSize) {
        Matrix kernel(kernelSize, kernelSize);
        for (int i = 0; i < kernelSize; ++i) {
            for (int j = 0; j < kernelSize; ++j) {
                kernel(i, j) = static_cast<uint8_t>(255.0 * getGaussianKernel(kernelSize, i, j));
            }
        }
        return applyKernel(kernel);
    }

    bool loadImage(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            return false;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (size < 2 || size % 2 != 0) {
            return false;
        }

        rows_ = size / (2 * sizeof(uint8_t));
        cols_ = 2;

        file.read(reinterpret_cast<char*>(p[0]), size / 2);
        file.read(reinterpret_cast<char*>(p[1]), size / 2);

        return true;
    }

    bool saveImage(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        file.write(reinterpret_cast<const char*>(p[0]), rows_ * cols_ * sizeof(uint8_t);
        file.write(reinterpret_cast<const char*>(p[1]), rows_ * cols_ * sizeof(uint8_t);

        return true;
    }

private:
    int rows_, cols_;
    double **p{};

};

#endif