cmake_minimum_required(VERSION 3.4)
project(Turing_infix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Turing_infix ${SOURCE_FILES})