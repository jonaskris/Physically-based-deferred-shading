cmake_minimum_required(VERSION 3.0)

add_subdirectory(image)

add_library(texture
    include/Texture.h
    include/TextureUnitManager.h src/TextureUnitManager.cpp)

target_include_directories(texture
    PUBLIC include)

target_link_libraries(texture
    PUBLIC image
    PUBLIC common
    PUBLIC glad)