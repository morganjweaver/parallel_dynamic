cmake_minimum_required(VERSION 3.6)
project(hw5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    similar.cpp)

add_executable(hw5 ${SOURCE_FILES})