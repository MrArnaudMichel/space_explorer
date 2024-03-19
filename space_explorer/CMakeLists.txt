cmake_minimum_required(VERSION 3.27)
project(Space_explorer C)

set(CMAKE_C_STANDARD 11)

add_executable(Space_explorer space_explorer.c space_solution.c)

# Link against the math library
target_link_libraries(Space_explorer m)
