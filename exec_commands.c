//
// Created by xenia on 20.03.23.
//
#include <dirent.h>
#include "exec_commands.h"

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
void execute(char **args) {
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

    sb_start(args);
}


void sb_start(char **args) {
    pid_t child_pid = fork();
    switch (child_pid) {
        case -1:
            perror("sb: fork failed");
            break;
        case 0:
            if (execvp(args[0], args) == -1)
                perror("sb: exec failed");
            exit(EXIT_FAILURE);
        default:
            while (waitpid(child_pid, (int *) 0, WNOHANG) != child_pid) {
                //ждем завершения процесса потомка
            }
    }
}

/* TO-DO:
 */

/* DONE:
 * help
 * cd
 * cat
 * ls
 * kill
 * exit
 */



void sb_help() {
    printf("This is a simple bash made by Xenia for my OS class.\n"
           "Type program names and arguments and hit enter.\n"
           "Supported commands are listed below:\n");

    for (int i = 0; i < sizeof(COMMANDS_INFO); i++)
        printf("    %s\n", COMMANDS_INFO[i]);
}

void sb_cd(char **args) {
    //Если в пеоеданной строке нет аргуметов
    if (args[1] == NULL) {
        printf("Expected a path in arguments\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("oops in cd");
        }
    }
}

void sb_cat(char **args){
    //Если в переданной строке нет аргументов
    if (args[1] == NULL) {
        printf("Expected files in arguments\n");
        return;
    }

    for(int i = 1; i < sizeof(args); ++i) {
        //Открываем файл только для чтения
        FILE  *file = fopen(args[i], "r");
        //Если не получается открыть файл, завершаем процесс
        if(file == NULL){
            printf("Error: cannot open the file: %s\n", args[i]);
            exit(EXIT_FAILURE);
        }
        //Посимвольно выводим содержимое файла,
        //пока не встречаем End Of File
        int ch;
        while((ch = fgetc(file)) != EOF){
            putchar(ch);
        }
        fclose(file);
    }
}

void sb_ls(char **args) {
    DIR *dir;
    //Если в переданной строке нет аргументов,
    //считываем текущую директорию
    if (args[1] == NULL) {
        dir = opendir(".");
    } else {
        if(args[2] != NULL)
            printf("Opening the first directory, "
                   "the rest of the arguments will be ignored\n");
        dir = opendir(args[1]);
    }

    if(dir == NULL){
        printf("Error: cannot open the directory: %s\n", args[1]);
        exit(EXIT_FAILURE);
    }

    //Выводим названия содержимого директории
    struct dirent *entry;
    while((entry = readdir(dir))) {
            printf("%s\n", entry->d_name);
    }
}

void sb_kill(int sig){
    printf("I got a signal %d. Press it again to stop execution\n", sig);
    (void) signal(SIGINT, SIG_DFL);
}

void sb_exit() {
    exit(EXIT_SUCCESS);
}