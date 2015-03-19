cmake_minimum_required(VERSION 2.8.4)
project(Fast_substring)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Fast_substring ${SOURCE_FILES})