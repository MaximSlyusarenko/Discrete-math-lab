cmake_minimum_required(VERSION 3.3)
project(Turing_ternary_to_binary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Turing_ternary_to_binary ${SOURCE_FILES})