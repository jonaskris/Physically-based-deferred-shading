cmake_minimum_required(VERSION 3.0)

add_executable(demo
    src/demo.cpp)

target_link_libraries(demo
    renderer
    geometry
    programs)