cmake_minimum_required(VERSION 3.27)
project(MatrixOOP VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
#include_directories(include/third_party_library)

# Add subdirectories
add_subdirectory(src)
#add_subdirectory(src/matrix)

add_library(MatrixOOP STATIC src/matrix/matrix.cpp src/matrix/matrix.h)

# gtest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(src/googletest EXCLUDE_FROM_ALL)
enable_testing()

add_executable(test_defaults tests/matrix_test.cpp)
target_include_directories(test_defaults PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(test_defaults gtest gtest_main ${PROJECT_NAME})
add_test(NAME test_defaults COMMAND test_defaults)