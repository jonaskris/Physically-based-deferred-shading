cmake_minimum_required(VERSION 3.0)

project(TestUtils)

add_library(testUtils
    include/TestUtils.h src/TestUtils.cpp)

target_include_directories(math
    PUBLIC include)

target_link_libraries(testUtils
    PUBLIC math)