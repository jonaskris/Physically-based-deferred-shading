cmake_minimum_required(VERSION 3.0)

add_library(common
    include/DataStore.h
    include/DataIdentifier.h
    include/Defines.h
    include/Source.h src/Source.cpp)

target_include_directories(common
    PUBLIC include)

set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)