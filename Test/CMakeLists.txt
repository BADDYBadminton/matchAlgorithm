cmake_minimum_required(VERSION 3.21)
project(Test)

set(CMAKE_CXX_STANDARD 14)

add_executable(Test main.cpp team.h team.cpp match.h match.cpp)
