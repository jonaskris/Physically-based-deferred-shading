cmake_minimum_required(VERSION 3.0)

ADD_CUSTOM_TARGET(resources ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_executable(demo
    src/demo.cpp)

target_link_libraries(demo
    programs
    rendering
    geometry
    model
    scene)