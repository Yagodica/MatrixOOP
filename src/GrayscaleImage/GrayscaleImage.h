#ifndef MATRIXOOP_GRAYSCALEIMAGE_H
#define MATRIXOOP_GRAYSCALEIMAGE_H

#include "matrix.h"
#include <iostream>
#include <string>

class GrayscaleImage {
public:
    GrayscaleImage(int width, int height);
    GrayscaleImage(const std::string& filename);
    void save(const std::string& filename);
    void applyBlurFilter();

private:
    Matrix pixels;
    int width;
    int height;
};


#endif //MATRIXOOP_GRAYSCALEIMAGE_H
