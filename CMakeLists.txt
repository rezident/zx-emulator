cmake_minimum_required(VERSION 3.2)
project(zx_emulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(zx_emulator ${SOURCE_FILES} hardware/Frequency.cpp hardware/Frequency.h)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(zx_emulator ${SDL2_LIBRARIES})