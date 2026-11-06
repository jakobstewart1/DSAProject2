cmake_minimum_required(VERSION 4.1)
project(DSAProject2)

set(CMAKE_CXX_STANDARD 20)

add_executable(DSAProject2 graph.cpp
        DFS.cpp
        BFS.cpp
        graph.h
        DFS.h
        BFS.h
        main.cpp)


enable_testing()

add_executable(BFS_TEST graph.cpp BFS.cpp BFS_TEST.cpp)
add_test(NAME BFS_TEST COMMAND BFS_TEST)

add_executable(DFS_TEST graph.cpp DFS.cpp DFS_TEST.cpp)
add_test(NAME DFS_TEST COMMAND DFS_TEST)