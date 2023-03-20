//
// Created by xenia on 20.03.23.
//
#include "exec_commands.h"

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
void execute(char **args)
{
    int i;

    if (args[0] == NULL) {
        // An empty command was entered.
        return;
    }

    for (i = 0; i < sizeof(COMMANDS); i++) {
        if (strcmp(args[0], COMMANDS[i]) == 0) {
            return (*commands_funcs[i])(args);
        }
    }

    //return lsh_launch(args);
}

/* TO-DO:
 * ls
 * cat
 * kill
 */

/* DONE:
 * help
 * cd
 * exit
 */



void sb_help(){
    printf("This is a simple bash made by Xenia for my OS class.\n");
    printf("Type program names and arguments and hit enter.\n");
    printf("Supported commands are listed below:\n");

    for(int i = 0; i < sizeof(COMMANDS_INFO); i++)
        printf("    %s\n", COMMANDS_INFO[i]);
}

void sb_cd(char **args){
    if (args[1] == NULL) {
        fprintf(stderr, "Expected a path in arguments\n");
    }
    else {
        if (chdir(args[1]) != 0) {
            perror("oops in cd");
        }
    }
}

void sb_exit(){
    exit(EXIT_SUCCESS);
}