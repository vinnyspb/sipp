cmake_minimum_required(VERSION 3.3)
project(sipp)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
  message("gcc/clang detected, adding compile flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")
endif()

add_subdirectory(tests)

