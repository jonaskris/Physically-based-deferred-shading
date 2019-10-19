cmake_minimum_required(VERSION 3.0)

project(Shaders)

add_library(shaders
    include/Shader.h src/Shader.cpp)

target_include_directories(shaders
    PUBLIC include)

target_link_libraries(shaders 
    PUBLIC glad
    PUBLIC glfw
    PUBLIC ${GLFW_LIBRARIES})