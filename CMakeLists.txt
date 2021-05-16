cmake_minimum_required(VERSION 3.17)
project(Computer_Systems C)

set(CMAKE_C_STANDARD 99)

add_executable(Computer_Systems main.c)

add_subdirectory(Test/)

add_executable(sequence assignment/assignment2/sequence.c assignment/assignment2/common.c assignment/assignment2/common.h)
add_executable(pipeline assignment/assignment2/pipeline.c assignment/assignment2/common.c assignment/assignment2/common.h)


add_executable(smsh1
        assignment/assignment3/execute.c
        assignment/assignment3/smsh1.c
        assignment/assignment3/splitline.c
        )
add_executable(smsh2
        assignment/assignment3/execute2.c
        assignment/assignment3/smsh2.c
        assignment/assignment3/splitline.c
        )
add_executable(smsh3
        assignment/assignment3/execute3.c
        assignment/assignment3/smsh3.c
        assignment/assignment3/splitline.c
        )
add_executable(smsh4
        assignment/assignment3/execute4.c
        assignment/assignment3/smsh3.c
        assignment/assignment3/splitline.c
        )