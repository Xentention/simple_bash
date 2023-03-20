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

#include "supported_commands.h"

void execute(char **args);
void sb_help();
void sb_cd(char **args);
void sb_exit();

void (*commands_funcs[]) (char **) = {
        &sb_help,
        &sb_cd,
        &sb_exit
};

#endif //SIMPLE_BASH_EXEC_COMMANDS_H