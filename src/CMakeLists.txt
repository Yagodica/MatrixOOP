cmake_minimum_required(VERSION 3.27)

# Include directories
include_directories(matrix)
include_directories(image)

# Add subdirectories
add_subdirectory(matrix)
add_subdirectory(image)
add_subdirectory(wxWidgets)

# Add executable
add_executable(project main.cpp)

if(UNIX)
    find_package(wxWidgets COMPONENTS net net core core base REQUIRED)
    target_link_libraries(project matrix image wx::net wx::core wx::base)
else()
    target_link_libraries(project matrix image wx::net wx::core wx::base)
endif()
