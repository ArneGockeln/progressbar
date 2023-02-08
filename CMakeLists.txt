cmake_minimum_required(VERSION 3.24)
project(progressbar C)

set(CMAKE_C_STANDARD 99)

add_executable(progressbar src/main.c src/progress.c src/progress.h)
