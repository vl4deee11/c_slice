cmake_minimum_required(VERSION 3.22)
project(c_slice C)

set(CMAKE_C_STANDARD 99)

add_executable(c_slice main.c slice.c slice.h)
