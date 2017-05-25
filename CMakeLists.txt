cmake_minimum_required(VERSION 3.3)
project(sipp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")

add_subdirectory(tests)

