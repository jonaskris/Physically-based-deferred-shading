cmake_minimum_required(VERSION 3.0)

add_library(window
    src/Window.cpp)

target_include_directories(window
    PUBLIC include)

target_link_libraries(window 
    PUBLIC glad
    PUBLIC glfw
    PUBLIC ${GLFW_LIBRARIES}
    PUBLIC input)

target_compile_definitions(window PRIVATE "GLFW_INCLUDE_NONE")