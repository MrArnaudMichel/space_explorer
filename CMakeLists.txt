cmake_minimum_required(VERSION 3.27)
project(C_Programming C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Programming
        main.c
        Lab6/rotate_matrix.c
        Lab6/rotateMatrix.h
        Lab7/student.c
        Lab7/student.h
        Lab7/structs.h
)
