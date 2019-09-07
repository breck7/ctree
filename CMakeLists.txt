cmake_minimum_required(VERSION 3.13)
project(ctree)

set(CMAKE_CXX_STANDARD 17)

add_executable(ctree main.cpp CTree.cpp CTree.h)
add_executable(tests CTree.cpp CTree.h catch.hpp tests.cpp)