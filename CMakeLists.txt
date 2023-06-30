cmake_minimum_required(VERSION 3.0)
project(2048)

add_executable(2048 2048.c)
target_link_libraries(2048 GL GLU glut m)
