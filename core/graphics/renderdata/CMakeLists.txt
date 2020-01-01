cmake_minimum_required(VERSION 3.0)

add_library(renderdata
    include/DataIdentifier.h
    include/Material.h src/Material.cpp
    include/Mesh.h src/Mesh.cpp
    include/Node.h
    include/Model.h src/Model.cpp
    include/Camera.h src/Camera.cpp
    include/RenderData.h
    include/Scene.h
    include/VertexAttribute.h)

target_include_directories(renderdata
    PUBLIC include)

target_link_libraries(renderdata 
    PUBLIC glad
    PUBLIC uniforms
    PUBLIC input)