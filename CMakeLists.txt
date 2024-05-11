cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FOO_PROJECT_NAME
        MatrixOOP
)

project(${FOO_PROJECT_NAME})

# Project

add_subdirectory(src)
add_subdirectory(tests)