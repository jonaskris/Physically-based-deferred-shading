cmake_minimum_required(VERSION 3.0)

project(Material)

add_library(material
    include/Material.h src/Material.cpp)

target_include_directories(material
    PUBLIC include)

target_link_libraries(material
    PUBLIC uniforms
    PUBLIC glad)