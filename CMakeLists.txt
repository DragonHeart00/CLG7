cmake_minimum_required(VERSION 3.19)
project(CLG7 C)

set(CMAKE_C_STANDARD 99)

add_executable(CLG7 GameLogic.c Controller.c main.c)