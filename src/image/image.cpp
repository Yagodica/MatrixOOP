#include "image.h"

Matrix Image::gaussianBlur(Matrix& image, double sigma, int ksize) {
    // Calculate the size of the Gaussian kernel
    int kernelSize = ksize * 2 + 1;

    // Create a 1D Gaussian kernel
    std::vector<double> gaussianKernel1D(kernelSize);
    double sum = 0.0;
    for (int i = 0; i < kernelSize; ++i) {
        double x = i - ksize;
        gaussianKernel1D[i] = exp(-0.5 * x * x / (sigma * sigma));
        sum += gaussianKernel1D[i];
    }

    // Normalize the Gaussian kernel
    for (int i = 0; i < kernelSize; ++i) {
        gaussianKernel1D[i] /= sum;
    }

    // Create a 2D Gaussian kernel
    Matrix gaussianKernel2D(kernelSize, kernelSize);
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            gaussianKernel2D(i, j) = gaussianKernel1D[i] * gaussianKernel1D[j];
        }
    }

    // Perform the Gaussian blur
    Matrix blurredImage(image.getRows(), image.getCols());
    for (int i = 0; i < image.getRows(); ++i) {
        for (int j = 0; j < image.getCols(); ++j) {
            double sum = 0.0;
            for (int m = -ksize; m <= ksize; ++m) {
                for (int n = -ksize; n <= ksize; ++n) {
                    int ii = i + m;
                    int jj = j + n;
                    if (ii >= 0 && ii < image.getRows() && jj >= 0 && jj < image.getCols()) {
                        sum += image(ii, jj) * gaussianKernel2D(m + ksize, n + ksize);
                    }
                }
            }
            blurredImage(i, j) = sum;
        }
    }

    return blurredImage;
}

// Function to read a matrix from a PGM file
Matrix Image::readMatrixFromPGMFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != "P5") {
        throw std::runtime_error("Invalid file format: " + filename);
    }

    int width, height;
    file >> width >> height;

    int maxValue;
    file >> maxValue;

    Matrix matrix(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            unsigned char value;
            file.read((char*)&value, sizeof(value));
            matrix(i, j) = double(value) / maxValue;
        }
    }

    return matrix;
}

// Function to save a matrix to a PGM file
void Image::saveMatrixToPGMFile(Matrix& matrix, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    file << "P5\n";
    file << matrix.getCols() << " " << matrix.getRows() << "\n";
    file << "255\n";

    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getCols(); ++j) {
            unsigned char value = static_cast<unsigned char>(std::round(matrix(i, j) * 255.0));
            file.write((char*)&value, sizeof(value));
        }
    }
}


