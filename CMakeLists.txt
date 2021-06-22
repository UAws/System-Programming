cmake_minimum_required(VERSION 3.17)
project(Computer_Systems C)

set(CMAKE_C_STANDARD 99)

add_executable(Computer_Systems main.c)

set(CMAKE_C_FLAGS "-std=c99 -Wall -pthread")

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
add_executable(05_early_exit Lecture/Lecture14/05_early_exit.c)
add_executable(06_detach Lecture/Lecture14/06_detach.c)
add_executable(07_thread_attr Lecture/Lecture14/07_thread_attr.c)
add_executable(01_sig_example Lecture/Lecture17-18/01_sig_example.c)
add_executable(02_race_condition Lecture/Lecture17-18/02_race_condition.c)
add_executable(03_read_example Lecture/Lecture17-18/03_read_example.c)
add_executable(05_sigaction_example Lecture/Lecture17-18/05_sigaction_example.c)
add_executable(04_ignore_example Lecture/Lecture17-18/04_ignore_example.c)
add_executable(01_async_demo Lecture/Lecture19-20/01_async_demo.c)
add_executable(02_aio_demo Lecture/Lecture19-20/02_aio_demo.c)
add_executable(03_strace_demo1 Lecture/Lecture19-20/03_strace_demo1.c)
add_executable(03_strace_demo2 Lecture/Lecture19-20/03_strace_demo2.c)
add_executable(03_strace_demo3 Lecture/Lecture19-20/03_strace_demo3.c)
add_executable(01_example_fdopen Lecture/Lecture21-22/01_example_fdopen.c)
add_executable(02_example_popen Lecture/Lecture21-22/02_example_popen.c)
add_executable(03_socket_client Lecture/Lecture21-22/03_socket_client.c)
add_executable(03_socket_server Lecture/Lecture21-22/03_socket_server.c)
add_executable(04_rw_client Lecture/Lecture21-22/04_rw_client.c)
add_executable(04_rw_server Lecture/Lecture21-22/04_rw_server.c)
add_executable(05_web_client Lecture/Lecture21-22/05_web_client.c)
add_executable(05_web_server Lecture/Lecture21-22/05_web_server.c)
add_executable(Q3_a Test/2018/Q3_a.c)
add_executable(print_doubleinput Test/2018/print_doubleinput.c)
add_executable(counter Test/2018/counter.c)
add_executable(stat Test/2018/stat.c)
add_executable(Q4_b Test/2018/Q4_b.c)
add_executable(Q4_c Test/2018/Q4_c.c)
add_executable(pipe Test/2018/pipe.c)
add_executable(2017_Q3_a Test/2017/2017_Q3_a.c)
add_executable(2017_Q5_a Test/2017/2017_Q5_a.c)
add_executable(2021-p4-q2 Test/2021/part4/2021-p4-q2.c)
add_executable(2021-p4-q5 Test/2021/part4/2021-p4-q5.c)
add_executable(2021-p5-q3 Test/2021/part5/2021-p5-q3.c)
add_executable(2021-p6-q2 Test/2021/part6/2021-p6-q2.c)