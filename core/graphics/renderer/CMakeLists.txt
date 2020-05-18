cmake_minimum_required(VERSION 3.0)

add_library(renderer
    include/Framebuffer.h
    include/Renderer.h src/Renderer.cpp)

target_include_directories(renderer
    PUBLIC include)

target_link_libraries(renderer 
    PUBLIC window
    PUBLIC scene
    PUBLIC program
    PUBLIC renderdata
    PUBLIC glad
    PUBLIC math)