cmake_minimum_required(VERSION 3.27)

# Include directories
include_directories(matrix)

# Add subdirectories
add_subdirectory(matrix)

# Add executable
add_executable(project main.cpp)
target_link_libraries(project matrix)
