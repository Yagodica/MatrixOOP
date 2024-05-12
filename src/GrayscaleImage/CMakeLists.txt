cmake_minimum_required(VERSION 3.27)

# Add library
add_library(GrayscaleImage GrayscaleImage.h GrayscaleImage.cpp)
target_link_libraries(GrayscaleImage matrix)
