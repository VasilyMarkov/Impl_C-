cmake_minimum_required(VERSION 3.5)

project(programm)
set(CMAKE_CXX_STANDARD 20)

enable_testing()
add_subdirectory(tests)

add_subdirectory(app)
