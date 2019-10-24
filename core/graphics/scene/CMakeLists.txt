cmake_minimum_required(VERSION 3.0)

project(Scene)

add_subdirectory(model)

add_library(scene
    include/Scene.h
    include/Camera.h src/Camera.cpp)

target_include_directories(scene
    PUBLIC include)

target_link_libraries(scene
    PUBLIC model
    PUBLIC math)