project(SettingsLib)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(SRC_LIST ./settings.cpp)
add_library(settings SHARED ${SRC_LIST})
#set(SRC_LIST ./settings.cpp ./main.cpp)
#add_executable(sett ${SRC_LIST})
