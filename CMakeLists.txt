cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)
set(SOURCE_LIB
    library/commonUtils/numericOperations.c
        Homework2/Task_1/linked_map.c
            Homework2/Task_2/dna_editor.c)
add_library(library ${SOURCE_LIB})

add_executable(task_1.1 Homework1/task1.c)
add_executable(task_1.2 Homework1/task_2.c)
add_executable(task_1.3 Homework1/task_3.c)
add_executable(task_1.4 Homework1/task_4.c)
add_executable(task_1.5 Homework1/task_5.c)
add_executable(task_2.1 Homework2/Task_1/task_1.c)
add_executable(task_2.2 Homework2/Task_2/task_2.c)
add_executable(task_3.1 Homework3/task_1.c)
add_executable(task_3.2 Homework3/task_2.c)
add_executable(task_3.3 Homework3/task_3.c)
add_executable(retest1_1.2 Retest1/test1_task2.c)
add_executable(Test2_task_1 Test2/task_1.c)
add_executable(Final_Test_task_1 Final_Test/task_1.c)

target_link_libraries(task_2.1 library)
target_link_libraries(task_2.2 library)
target_link_libraries(task_2.1 library)
