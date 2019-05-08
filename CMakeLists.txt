cmake_minimum_required(VERSION 3.13)
project(algo CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(module_1.1_1 module_1/1_1/main.cpp)
add_executable(module_1.1_2 module_1/2_1/main.cpp)
add_executable(module_1.1_3 module_1/3_1/main.cpp)
add_executable(module_1.1_4 module_1/4_2/main.cpp)
add_executable(module_1.1_5 module_1/5_3/main.cpp)
add_executable(module_1.1_6 module_1/6_2/main.cpp)
add_executable(module_1.1_7 module_1/7_1/main.cpp)

add_executable(module_2.1_1 module_2/1_1/main.cpp)
add_executable(module_2.2_1 module_2/2_1/main.cpp)

add_executable(
        module_3.1
        module_3/1/main.cpp
        module_3/1/c_matrix_graph.cpp
        module_3/1/c_list_graph.cpp
        module_3/1/c_set_graph.cpp
        module_3/1/c_arc_graph.cpp
)
add_executable(module_3.2 module_3/2/main.cpp)