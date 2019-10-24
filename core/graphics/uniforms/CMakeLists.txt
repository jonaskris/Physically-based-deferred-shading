cmake_minimum_required(VERSION 3.0)

project(Uniforms)

add_library(uniforms
    include/Sampler.h src/Sampler.cpp
    include/Uniform.h src/Uniform.cpp
    include/TextureUnitManager.h src/TextureUnitManager.cpp)

target_include_directories(uniforms
    PUBLIC include)

target_link_libraries(uniforms
    PUBLIC math
    PUBLIC stb_image
    PUBLIC glad)