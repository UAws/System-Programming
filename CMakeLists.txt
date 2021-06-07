cmake_minimum_required(VERSION 3.17)
project(Computer_Systems C)

set(CMAKE_C_STANDARD 99)

add_executable(Computer_Systems main.c)

set(CMAKE_C_FLAGS "-std=c99 -Wall -lpthread")

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
add_executable(01_test_threads Lecture/Lecture14/01_test_threads.c)
add_executable(02_flip_flop Lecture/Lecture14/02_flip_flop.c)
add_executable(03_race_condition Lecture/Lecture14/03_race_condition.c)
add_executable(04_mutex Lecture/Lecture14/04_mutex.c)
add_executable(Q8 Test/MiniExam/Q8.c)

add_executable(assignment4_part1
        assignment/assignment4/slow_functions.c
        assignment/assignment4/part1.c)

add_executable(assignment4_part2
        assignment/assignment4/slow_functions.c
        assignment/assignment4/part2.c)
add_executable(08_signal Lecture/Lecture14/08_signal.c)