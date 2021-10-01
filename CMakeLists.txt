cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)
set(SOURCE_LIB
    library/commonUtils/numericOperations.c Homework2/Task_1/linked_map.c)
add_library(library ${SOURCE_LIB})

add_executable(task_2 Homework1/task_2.c)
add_executable(task_3 Homework1/task_3.c)
add_executable(task_4 Homework1/task_4.c)
add_executable(task_5 Homework1/task_5.c)
add_executable(task_2_1 Homework2/Task_1/task_1.c)
target_link_libraries(task_2_1 library)