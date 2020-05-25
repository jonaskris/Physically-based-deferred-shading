cmake_minimum_required(VERSION 3.0)

add_library(program
    include/Program.h src/Program.cpp
    include/ProgramStore.h src/ProgramStore.cpp
    include/Shader.h src/Shader.cpp)
    
target_include_directories(program
    PUBLIC include)

target_link_libraries(program
    PUBLIC common
    PUBLIC math
    PUBLIC glad
    PUBLIC texture)