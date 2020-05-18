cmake_minimum_required(VERSION 3.0)

add_library(scene
    include/Scene.h
    include/Node.h
    include/Skybox.h src/Skybox.cpp
    include/Camera.h src/Camera.cpp
    include/AssimpLoader.h src/AssimpLoader.cpp)

target_include_directories(scene
    PUBLIC include)

target_link_libraries(scene
    PUBLIC common
    PUBLIC renderdata
    PUBLIC program
    PUBLIC input
    PUBLIC geometry
    PUBLIC math
    PUBLIC assimp
    PUBLIC glad)