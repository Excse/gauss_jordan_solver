cmake_minimum_required(VERSION 3.0)
project(GaussJordan)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES src/gauss.cpp tests/test_gauss.cpp)

include_directories(include)

add_subdirectory(googletest)

add_executable(GaussJordan ${SOURCE_FILES})

target_link_libraries(GaussJordan gtest gtest_main)

