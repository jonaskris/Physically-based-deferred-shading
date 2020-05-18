cmake_minimum_required(VERSION 3.0)

add_library(renderdata
    include/DrawUnit.h
    include/DrawKey.h
    include/Mesh.h
    include/RenderQueue.h
    include/Material.h src/Material.cpp)

target_include_directories(renderdata
    PUBLIC include)

target_link_libraries(renderdata
    PUBLIC common
    PUBLIC scene
    PUBLIC program
    PUBLIC geometry
    PUBLIC math)