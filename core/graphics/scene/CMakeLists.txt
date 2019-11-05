cmake_minimum_required(VERSION 3.0)

project(Scene)

add_library(scene
    include/Scene.h
    include/Node.h 
    include/Model.h 
    include/Camera.h src/Camera.cpp)

target_include_directories(scene
    PUBLIC include)

target_link_libraries(scene
    PUBLIC uniforms
    PUBLIC material
    PUBLIC glad)