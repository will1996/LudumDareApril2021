# CMakeList.txt : CMake project for LudumDareApril2021, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_subdirectory(Willow)
add_executable (LudumDareApril2021 "LudumDareApril2021.cpp"  "Maze.cpp" "Maze.hpp")
include(Willow/CMake/WillowProject.cmake)
WILLOWAPPLICATION(LudumDareApril2021)


# TODO: Add tests and install targets if needed.
