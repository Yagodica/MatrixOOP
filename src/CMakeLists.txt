cmake_minimum_required(VERSION 3.27)

# Include directories
include_directories(matrix)
include_directories(image)

# Add subdirectories
add_subdirectory(matrix)
add_subdirectory(image)

# Add executable
add_executable(project main.cpp)
target_link_libraries(project matrix image)
