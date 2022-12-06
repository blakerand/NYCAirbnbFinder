cmake_minimum_required(VERSION 3.24)
project(NYCAirbnbFinder)

set(CMAKE_CXX_STANDARD 14)

add_executable(NYCAirbnbFinder
        graph.cpp
        main.cpp
        map.cpp)
