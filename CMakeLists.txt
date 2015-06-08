cmake_minimum_required(VERSION 3.2)
project(zx_emulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(zx_emulator ${SOURCE_FILES})