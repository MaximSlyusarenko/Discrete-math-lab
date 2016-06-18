cmake_minimum_required(VERSION 3.4)
project(Turing_sort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES checker.cpp)
add_executable(Turing_sort ${SOURCE_FILES})