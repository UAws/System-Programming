cmake_minimum_required(VERSION 3.17)
project(Computer_Systems C)

set(CMAKE_C_STANDARD 99)

add_executable(Computer_Systems main.c)


add_executable(sequence assignment/assignment2/sequence.c assignment/assignment2/common.c assignment/assignment2/common.h)
add_executable(pipeline assignment/assignment2/pipeline.c assignment/assignment2/common.c assignment/assignment2/common.h)