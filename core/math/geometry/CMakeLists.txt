cmake_minimum_required(VERSION 3.0)

project(Geometry)

add_library(geometry
    include/Mesh.h
    include/Icosphere.h
    include/Cube.h
    include/Plane.h
    include/AxisTriplets.h)

target_include_directories(geometry
    PUBLIC include)

target_link_libraries(geometry 
    PUBLIC math
    PUBLIC glad)