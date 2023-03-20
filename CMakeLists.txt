cmake_minimum_required(VERSION 3.24)
project(simple_bash C)

set(CMAKE_C_STANDARD 11)

add_executable(simple_bash main.c main.h parse_lines.c exec_commands.h exec_commands.c parse_lines.h supported_commands.h)
