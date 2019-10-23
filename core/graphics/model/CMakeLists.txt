cmake_minimum_required(VERSION 3.0)

project(Model)

add_library(model
    include/Model.h src/Model.cpp
    include/Uniform.h src/Uniform.cpp)

target_include_directories(model
    PUBLIC include)

target_link_libraries(model
    PUBLIC math
    PUBLIC geometry
    PUBLIC glad)