cmake_minimum_required(VERSION 3.0)

add_library(image
    include/Image.h src/Image.cpp)

target_include_directories(image
    PUBLIC include)

target_link_libraries(image
    PUBLIC common
    PUBLIC stb_image)