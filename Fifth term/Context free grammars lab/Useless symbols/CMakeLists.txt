cmake_minimum_required(VERSION 3.3)
project(Useless_symbols)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Useless_symbols ${SOURCE_FILES})