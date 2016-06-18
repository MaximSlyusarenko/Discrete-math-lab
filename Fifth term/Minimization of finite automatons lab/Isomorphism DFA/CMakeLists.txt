cmake_minimum_required(VERSION 3.3)
project(Isomorphism_DFA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Isomorphism_DFA ${SOURCE_FILES})