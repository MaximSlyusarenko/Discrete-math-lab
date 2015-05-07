cmake_minimum_required(VERSION 3.1)
project(Schedule_Matroids)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Schedule_Matroids ${SOURCE_FILES})