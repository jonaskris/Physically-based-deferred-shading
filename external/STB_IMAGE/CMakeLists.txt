cmake_minimum_required(VERSION 3.0)

project(STB_IMAGE)

add_library(stb_image INTERFACE)

target_include_directories(stb_image INTERFACE include)