cmake_minimum_required(VERSION 3.0)
enable_testing()

project(PhysicallyBasedDeferredShading)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(external/GLAD)
add_subdirectory(external/GLFW)
add_subdirectory(external/STB_IMAGE)
add_subdirectory(external/googletest)
add_subdirectory(external/Assimp)
add_subdirectory(core)
add_subdirectory(demo)

add_subdirectory(tests)
