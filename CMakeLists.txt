cmake_minimum_required(VERSION 3.27)
project(MatrixOOP VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include/third_party_library)

# Add subdirectories
add_subdirectory(src)
#add_subdirectory(tests)