cmake_minimum_required(VERSION 3.0)

project(Math)

add_library(math
    include/Vec2.h src/Vec2.cpp
    include/Vec3.h src/Vec3.cpp
    include/Vec4.h src/Vec4.cpp
    include/Mat4.h src/Mat4.cpp
    include/Quaternion.h src/Quaternion.cpp
    include/Transform.h
    include/Degrees.h src/Degrees.cpp
    include/Radians.h src/Radians.cpp
    include/Utils.h)

target_include_directories(math
    PUBLIC include)

target_link_libraries(math
    PUBLIC gtest 
    PUBLIC gtest_main)

add_subdirectory(geometry)