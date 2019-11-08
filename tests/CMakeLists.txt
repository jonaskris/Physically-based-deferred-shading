cmake_minimum_required(VERSION 3.0)

project(Tests)

add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Mat4
add_executable(Mat4_Tests Mat4_Tests.cpp)
target_link_libraries(Mat4_Tests 
    PRIVATE gtest 
    PRIVATE gtest_main
    PRIVATE math)
add_test(Mat4 Mat4_Tests)

# Vec4
add_executable(Vec4_Tests Vec4_Tests.cpp)
target_link_libraries(Vec4_Tests 
    PRIVATE gtest 
    PRIVATE gtest_main
    PRIVATE math)
add_test(Vec4 Vec4_Tests)

# Vec3
add_executable(Vec3_Tests Vec3_Tests.cpp)
target_link_libraries(Vec3_Tests 
    PRIVATE gtest 
    PRIVATE gtest_main
    PRIVATE math)
add_test(Vec3 Vec3_Tests)

# Vec2
add_executable(Vec2_Tests Vec2_Tests.cpp)
target_link_libraries(Vec2_Tests 
    PRIVATE gtest 
    PRIVATE gtest_main
    PRIVATE math)
add_test(Vec2 Vec2_Tests)