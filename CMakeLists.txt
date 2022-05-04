cmake_minimum_required(VERSION 3.21)
project(hex_viewer)

set(CMAKE_CXX_STANDARD 14)

add_executable(hex_viewer main.cpp helperFunctions.h helperFunctions.cpp)
