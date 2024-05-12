#include "GrayscaleImage.h"

GrayscaleImage::GrayscaleImage(int width, int height) : width(width), height(height), pixels(height, width) {}

GrayscaleImage::GrayscaleImage(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    std::getline(file, line); // Пропускаем первую строку с комментарием
    std::getline(file, line); // Считываем размеры изображения
    std::istringstream iss(line);
    int w, h;
    iss >> w >> h;
    width = w;
    height = h;
    pixels = Matrix(height, width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> pixels(i, j);
        }
    }
}

void GrayscaleImage::save(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    file << "P2\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file << static_cast<int>(pixels(i, j)) << " ";
        }
        file << "\n";
    }
}

void GrayscaleImage::applyBlurFilter() {
    Matrix blur_kernel = Matrix({{0.0625, 0.125, 0.0625},
                                 {0.125,  0.25,  0.125},
                                 {0.0625, 0.125, 0.0625}});
    Matrix temp_pixels = pixels;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double sum = 0.0;
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    int x = i + k;
                    int y = j + l;
                    if (x >= 0 && x < height && y >= 0 && y < width) {
                        sum += temp_pixels(x, y) * blur_kernel(k + 1, l + 1);
                    }
                }
            }
            pixels(i, j) = sum;
        }
    }
}