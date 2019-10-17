cmake_minimum_required(VERSION 3.0)

project(Renderer)

add_library(renderer
    include/Renderer.h src/Renderer.cpp
    include/Framebuffer.h src/Framebuffer.cpp)

target_include_directories(renderer
    PUBLIC include)

target_link_libraries(renderer 
    PUBLIC math
    PUBLIC geometry
    PUBLIC glad)
    #PUBLIC glfw
    #PUBLIC ${GLFW_LIBRARIES})

target_compile_definitions(geometry PRIVATE "GLFW_INCLUDE_NONE")