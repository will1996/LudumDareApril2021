# CMakeList.txt : CMake project for LudumDareApril2021, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("LudumDareApril2021")

set(CMAKE_CXX_STANDARD 20)

# Add source to this project's executable.
add_subdirectory(Willow)

add_executable (RabbitHole "LudumDareApril2021.cpp"  "Maze.cpp" "Maze.hpp" SceneBuilder.cpp SceneBuilder.hpp MazeBuilder.cpp MazeBuilder.hpp CollisionGraph.cpp CollisionGraph.hpp)

include(Willow/CMake/WillowProject.cmake)
WillowApplication(RabbitHole)

# TODO: Add tests and install targets if needed.
