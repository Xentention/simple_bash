//
// Created by xenia on 20.03.23.
//

#ifndef SIMPLE_BASH_EXEC_COMMANDS_H
#define SIMPLE_BASH_EXEC_COMMANDS_H

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void execute(char **args);
void sb_start(char **args);

void sb_help();
void sb_cd(char **args);
void sb_cat(char **args);
void sb_ls(char **args);
void sb_kill(char **args);

extern const char NUM_COMMANDS;
extern void (*commands_funcs[]) (char **);
extern const char* COMMANDS[];
extern const char* COMMANDS_INFO[];

#endif //SIMPLE_BASH_EXEC_COMMANDS_H