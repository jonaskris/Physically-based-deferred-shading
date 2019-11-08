cmake_minimum_required(VERSION 3.0)

add_library(rendering
    include/Framebuffer.h src/Framebuffer.cpp
    include/Renderer.h src/Renderer.cpp)

target_include_directories(rendering
    PUBLIC include)

target_link_libraries(rendering 
    PUBLIC window
    PUBLIC programs
    PUBLIC scene
    PUBLIC glad
    PUBLIC uniforms)