cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(external/GLAD)
add_subdirectory(external/GLFW)
add_subdirectory(core)
add_subdirectory(demo)