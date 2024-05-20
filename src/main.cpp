#include <iostream>
#include <string>
#include "matrix/matrix.h"
#include "image/image.h"

using namespace std;

int main() {
    try {
        // Считывание изображения из PGM-файла
        Image image(5.0, 5, "input.pgm");

        // Примените к изображению размытие по Гауссу
        image.applyGaussianBlur();

        // Сохранение результата в новом PGM-файле
        image.saveToPGMFile("output_test.pgm");

        cout << "Размытие по Гауссу успешно применено к изображению и сохранено в файл." << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
