cmake_minimum_required(VERSION 2.8.4)
project(Calculator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(Calculator Calculator.cpp)
