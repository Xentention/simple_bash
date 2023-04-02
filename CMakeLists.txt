cmake_minimum_required(VERSION 3.24)
project(simple_bash C)

set(CMAKE_C_STANDARD 11)

add_executable(simple_bash src/main.c src/main.h src/parse_lines.c src/exec_commands.h
        src/exec_commands.c src/parse_lines.h)
