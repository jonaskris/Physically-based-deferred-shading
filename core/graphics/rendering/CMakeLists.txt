cmake_minimum_required(VERSION 3.0)

project(Renderering)

add_library(rendering
    include/RenderManager.h src/RenderManager.cpp
    include/Renderer.h
    include/ForwardRenderer.h src/ForwardRenderer.cpp)

target_include_directories(rendering
    PUBLIC include)

target_link_libraries(rendering 
    PUBLIC window
    PUBLIC programs
    PUBLIC glad)