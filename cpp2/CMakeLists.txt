cmake_minimum_required(VERSION 2.8)

project(cpp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -Wno-unused-parameter")

add_executable(step0_repl step0_repl.cpp)
add_executable(step1_read_print
step1_read_print.cpp
Reader.cpp
printer.cpp
types.cpp
)


include_directories(variant/include)
