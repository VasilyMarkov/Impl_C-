cmake_minimum_required(VERSION 3.5)

project(app LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(app main.cpp)
