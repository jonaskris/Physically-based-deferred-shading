cmake_minimum_required(VERSION 3.0)

project(Scene)

add_library(scene
    include/Scene.h src/Scene.cpp
    include/Camera.h src/Camera.cpp)

target_link_libraries(scene
    PUBLIC model
    PUBLIC geometry
    PUBLIC math)