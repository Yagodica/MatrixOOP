cmake_minimum_required(VERSION 3.27)

# Include directories
include_directories(matrix)
include_directories(GrayscaleImage)

# Add subdirectories
add_subdirectory(matrix)
add_subdirectory(GrayscaleImage)

# Add executable
add_executable(project_name main.cpp)
target_link_libraries(project_name matrix GrayscaleImage)
