cmake_minimum_required(VERSION 3.24)
project(ESONERO C)

set(CMAKE_C_STANDARD 11)

add_executable(ESONERO main.c gamelib.c gamelib.h)
