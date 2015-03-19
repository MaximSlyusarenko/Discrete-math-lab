cmake_minimum_required(VERSION 2.8.4)
project(Naive_substring)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Naive_substring ${SOURCE_FILES})