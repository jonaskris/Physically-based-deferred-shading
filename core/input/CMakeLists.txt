cmake_minimum_required(VERSION 3.0)

project(Input)

add_library(input
    include/KeyboardCallback.h src/KeyboardCallback.cpp
    include/MouseCallback.h src/MouseCallback.cpp
    include/TimeCallback.h src/TimeCallback.cpp
    include/KeyboardListener.h
    include/MouseListener.h
    include/TimeListener.h
    include/Input.h src/Input.cpp
    include/InputEnums.h)

target_include_directories(input
    PUBLIC include)

target_link_libraries(input 
    PUBLIC glfw
    PUBLIC ${GLFW_LIBRARIES}
    PUBLIC math)

target_compile_definitions(input PRIVATE "GLFW_INCLUDE_NONE")