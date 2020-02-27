cmake_minimum_required(VERSION 3.0)

add_library(renderdata
    include/DataIdentifier.h
    include/RenderData.h
    include/Mesh.h
    include/Model.h)

target_include_directories(renderdata
    PUBLIC include)

target_link_libraries(renderdata 
    PUBLIC glad
    PUBLIC uniforms
    PUBLIC input
    PUBLIC assimp)