cmake_minimum_required(VERSION 3.0)

project(Geometry)

add_library(geometry
    include/Mesh.h src/Mesh.cpp
    include/Icosphere.h src/Icosphere.cpp
    include/Cube.h src/Cube.cpp
    include/Plane.h src/Plane.cpp)

target_include_directories(geometry
    PUBLIC include)

target_link_libraries(geometry 
    PUBLIC math
    PUBLIC glad
    PUBLIC glfw
    PUBLIC ${GLFW_LIBRARIES})

target_compile_definitions(geometry PRIVATE "GLFW_INCLUDE_NONE")