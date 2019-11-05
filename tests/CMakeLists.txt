cmake_minimum_required(VERSION 3.0)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Mat4
add_executable(Mat4_Tests Mat4_Tests.cpp)
target_link_libraries(Mat4_Tests 
    PRIVATE gtest 
    PRIVATE gtest_main
    PRIVATE math)

add_test(Mat4 Mat4_Tests)