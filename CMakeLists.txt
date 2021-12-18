cmake_minimum_required(VERSION 3.21)
project(Akinator)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Akinator
        include/Akinator.h
        src/Akinator_Func.cpp
        src/Akinator_Main.cpp)
