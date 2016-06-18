cmake_minimum_required(VERSION 3.3)
project(Khomskiy_normal_form)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Khomskiy_normal_form ${SOURCE_FILES})