cmake_minimum_required(VERSION 3.0)
project(GaussJordan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES src/solver.cpp src/pbma.cpp src/matrix.cpp src/main.cpp)

include_directories(include)

add_executable(GaussJordan ${SOURCE_FILES})
