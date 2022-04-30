cmake_minimum_required(VERSION 3.21)
project(Project_PDP_11 C)

set(CMAKE_C_STANDARD 99)

add_executable(Project_PDP_11 main.c wordmem.c run.h interface.h commands.h)
