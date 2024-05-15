#include <iostream>
#include <vector>
#include <fstream>

class Matrix {
public:
    Matrix(int rows, int cols) : data(rows, std::vector<int>(cols)), rows(rows), cols(cols) {}

    int& operator()(int row, int col) {
        return data[row][col];
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

private:
    std::vector<std::vector<int>> data;
    int rows;
    int cols;
};

Matrix loadImage(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file 1" << std::endl;
        exit(1);
    }

    int width, height;
    file.read(reinterpret_cast<char*>(&width), sizeof(width));
    file.read(reinterpret_cast<char*>(&height), sizeof(height));

    Matrix image(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int value;
            file.read(reinterpret_cast<char*>(&value), sizeof(value));
            image(i, j) = value;
        }
    }

    return image;
}

void saveImage(const std::string& filename, Matrix& image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file 2" << std::endl;
        exit(1);
    }

    int width = image.getCols();
    int height = image.getRows();
    file.write(reinterpret_cast<const char*>(&width), sizeof(width));
    file.write(reinterpret_cast<const char*>(&height), sizeof(height));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int value = image(i, j);
            file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }
    }
}

Matrix toGrayscale(Matrix& image) {
    Matrix gray(image.getRows(), image.getCols());
    for (int i = 0; i < image.getRows(); i++) {
        for (int j = 0; j < image.getCols(); j++) {
            int r = image(i, j * 3);
            int g = image(i, j * 3 + 1);
            int b = image(i, j * 3 + 2);
            int grayValue = (r + g + b) / 3;
            gray(i, j) = grayValue;
        }
    }
    return gray;
}

Matrix binarize(Matrix& image, int threshold) {
    Matrix binary(image.getRows(), image.getCols());
    for (int i = 0; i < image.getRows(); i++) {
        for (int j = 0; j < image.getCols(); j++) {
            binary(i, j) = image(i, j) > threshold ? 255 : 0;
        }
    }
    return binary;
}

