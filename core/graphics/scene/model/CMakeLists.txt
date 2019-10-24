cmake_minimum_required(VERSION 3.0)

project(Model)

add_library(model
    include/Model.h src/Model.cpp)

target_include_directories(model
    PUBLIC include)

target_link_libraries(model
    PUBLIC geometry
    PUBLIC uniforms
    PUBLIC glad)