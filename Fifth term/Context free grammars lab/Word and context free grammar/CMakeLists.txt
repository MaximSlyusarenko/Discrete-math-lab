cmake_minimum_required(VERSION 3.3)
project(Word_and_context_free_grammar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Word_and_context_free_grammar ${SOURCE_FILES})