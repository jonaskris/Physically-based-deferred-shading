cmake_minimum_required(VERSION 3.0)

project(Programs)

add_subdirectory(shaders)

add_library(programs
    include/Program.h src/Program.cpp)

target_include_directories(programs
    PUBLIC include)

target_link_libraries(programs
    PUBLIC shaders
    PUBLIC glad
    PUBLIC glfw
    PUBLIC ${GLFW_LIBRARIES})