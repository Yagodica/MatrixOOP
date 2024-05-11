cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project

add_library(matrix matrix/matrix.cpp matrix/matrix.h)
#add_library(Image Image/Image.cpp Image/Image.h)
add_library(GrayscaleImage GrayscaleImage/GrayscaleImage.cpp GrayscaleImage/GrayscaleImage.h)

#target_link_libraries(GrayscaleImage PRIVATE Image)

add_executable(project_name main.cpp)
target_link_libraries(project_name PRIVATE matrix GrayscaleImage)


target_include_directories(matrix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/matrix)
#target_include_directories(Image PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Image)
target_include_directories(GrayscaleImage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/GrayscaleImage)
