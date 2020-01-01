cmake_minimum_required(VERSION 3.0)

add_library(uniforms
    include/Uniform.h src/Uniform.cpp)

target_include_directories(uniforms
    PUBLIC include)

target_link_libraries(uniforms
    PUBLIC math
    PUBLIC glad
    PUBLIC texture)