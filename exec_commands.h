//
// Created by xenia on 20.03.23.
//

#ifndef SIMPLE_BASH_EXEC_COMMANDS_H
#define SIMPLE_BASH_EXEC_COMMANDS_H

//#include "main.h"
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char* COMMANDS[] = {
        "help",
        "cd",
        "cat",
        "ls"
};

const char* COMMANDS_INFO[] = {
        "help - information about built-in commands",
        "cd <path> - move to the directory",
        "cat <file(s)> - to read files",
        "ls - display a list of files and sub-directories in the current directory"
};

void execute(char **args);
void sb_start(char **args);

void sb_help();
void sb_cd(char **args);
void sb_cat(char **args);
void sb_ls(char **args);
void sb_kill(int sig);
void sb_exit();

void (*commands_funcs[]) (char **) = {
        &sb_help,
        &sb_cd,
        &sb_cat,
        &sb_ls,
        &sb_exit
};

#endif //SIMPLE_BASH_EXEC_COMMANDS_H