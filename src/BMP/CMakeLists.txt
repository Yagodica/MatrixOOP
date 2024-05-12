cmake_minimum_required(VERSION 3.27)

# Add library
add_library(BMP BMP.h)
target_link_libraries(BMP matrix)
