cmake_minimum_required(VERSION 3.0)

project(Input)

add_library(input
    include/Keyboard.h src/Keyboard.cpp 
    include/Mouse.h src/Mouse.cpp)

target_include_directories(input
    PUBLIC include)

target_link_libraries(input 
    PUBLIC glfw
    PUBLIC ${GLFW_LIBRARIES})

target_compile_definitions(input PRIVATE "GLFW_INCLUDE_NONE")