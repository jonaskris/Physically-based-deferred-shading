cmake_minimum_required(VERSION 3.0)

project(Geometry)

add_library(geometry
    include/Icosphere.h
    include/Cube.h src/Cube.cpp
    include/Plane.h src/Plane.cpp
    include/AxisTriplets.h)

target_include_directories(geometry
    PUBLIC include)

target_link_libraries(geometry 
    PUBLIC math
    PUBLIC renderdata
    PUBLIC glad)