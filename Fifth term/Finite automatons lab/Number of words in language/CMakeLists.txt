cmake_minimum_required(VERSION 3.3)
project(Number_of_words_in_language)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Number_of_words_in_language ${SOURCE_FILES})