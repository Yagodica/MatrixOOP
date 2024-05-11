#include "GrayscaleImage.h"

//GrayscaleImage::GrayscaleImage(int width, int height) : width(width), height(height) {
//    Matrix pixels(width, height);
//}
//
//GrayscaleImage::GrayscaleImage(const std::string& filename) {
//    // Загрузить изображение из файла и заполнить pixels
//}
//
//void GrayscaleImage::save(const std::string& filename) {
//    // Сохранить изображение в файл
//}
//
//void GrayscaleImage::applyBlurFilter() {
//    Matrix blurred(height, std::vector<int>(width));
//
//    // Определите фильтр размытия 3x3
//    std::vector<std::vector<double>> blurFilter = {
//            {1.0 / 16, 1.0 / 8, 1.0 / 16},
//            {1.0 / 8, 1.0 / 4, 1.0 / 8},
//            {1.0 / 16, 1.0 / 8, 1.0 / 16}
//    };
//
//    for (int i = 0; i < height; ++i) {
//        for (int j = 0; j < width; ++j) {
//            double newPixelValue = 0.0;
//
//            // Применить фильтр размытия к текущему пикселю
//            for (int k = -1; k <= 1; ++k) {
//                for (int l = -1; l <= 1; ++l) {
//                    int row = i + k;
//                    int col = j + l;
//
//                    // Пропустить пиксели за пределами изображения
//                    if (row >= 0 && row < height && col >= 0 && col < width) {
//                        newPixelValue += pixels[row][col] * blurFilter[k + 1][l + 1];
//                    }
//                }
//            }
//
//            // Ограничить значение пикселя диапазоном [0, 255] и привести к целому числу
//            blurred[i][j] = std::clamp(static_cast<int>(std::round(newPixelValue)), 0, 255);
//        }
//    }
//
//    pixels = blurred;
//}

