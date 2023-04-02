//
// Created by xenia on 20.03.23.
//

#include <dirent.h>
#include "exec_commands.h"

/**
 * @brief Enumeration of functions supporting builtin commands
 */
void (*commands_funcs[])(char **) = {
        &sb_help,
        &sb_cd,
        &sb_cat,
        &sb_ls,
        &sb_exit
};

/**
 * @brief Builtin commands
 */
const char *COMMANDS[] = {
        "help",
        "cd",
        "cat",
        "ls",
        "exit"
};

/**
 * @brief Brief info about builtin commands
 */
const char *COMMANDS_INFO[] = {
        "help - information about built-in commands",
        "cd <path> - move to the directory",
        "cat <file(s)> - to read files",
        "ls - display a list of files and sub-directories in the current directory",
        "exit - finishes the program"
};

/**
 * @brief Number of builtin commands
 */
const char NUM_COMMANDS = sizeof(COMMANDS) / sizeof(char *);


 /**
  * @brief Executes shell builtins or launches programs
  * @param args Null terminated list of arguments
  */
void execute(char **args) {
    if (args[0] == NULL) {
        // An empty command was entered.
        return;
    }

    for (int i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(args[0], COMMANDS[i]) == 0) {
            return (*commands_funcs[i])(args);
        }
    }

    sb_start(args);
}

/**
 * @brief Starts a new process using fork-exec
 * @param args Null terminated list of arguments
 */
void sb_start(char **args) {
    pid_t child_pid = fork();
    switch (child_pid) {
        case -1:
            perror("Error: fork failed");
            break;
        case 0:
            (void) signal(SIGINT, SIG_DFL);
            if (execvp(args[0], args) == -1)
                perror("Error: command execution failed");
            exit(EXIT_FAILURE);
        default:
            while (waitpid(child_pid, (int *) 0, WNOHANG) != child_pid) {
                //ждем завершения процесса потомка
            }
    }
}

/**
 * @brief Prints an information about builtin commands
 */
void sb_help() {
    printf("This is a simple bash made by Xenia for my OS class.\n"
           "Type program names and arguments and hit enter.\n"
           "Builtin commands are listed below:\n");

    for (int i = 0; i < NUM_COMMANDS; i++)
        printf("    %s\n", COMMANDS_INFO[i]);
}

void sb_cd(char **args) {
    //Если в пеоеданной строке нет аргуметов
    if (args[1] == NULL) {
        printf("Expected a path in arguments\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("Error in cd: No such file or directory");
        }
    }
}

/**
 * @brief Prints the files' contents
 * @param args Null terminated list of arguments
 */
void sb_cat(char **args) {
    //Если в переданной строке нет аргументов
    if (args[1] == NULL) {
        printf("Expected files in arguments\n");
        return;
    }

    for (int i = 1; i < sizeof(args) / sizeof(char); ++i) {
        if(args[i] == NULL)
            return;
        //Открываем файл только для чтения
        FILE *file = fopen(args[i], "r");
        //Если не получается открыть файл, завершаем процесс
        if (file == NULL) {
            printf("Error: cannot open the file: %s\n", args[i]);
            return;
        }
        //Посимвольно выводим содержимое файла,
        //пока не встречаем End Of File
        int ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        fclose(file);
    }
}

/**
 * @brief Prints all files and subdirectories in \<path>.
 *        If args is empty, then in the current directory
 * @param args Null terminated list of arguments
 */
void sb_ls(char **args) {
    DIR *dir;
    //Если в переданной строке нет аргументов,
    //считываем текущую директорию
    if (args[1] == NULL) {
        dir = opendir(".");
    } else {
        if (args[2] != NULL)
            printf("Opening the first directory, "
                   "the rest of the arguments will be ignored\n");
        dir = opendir(args[1]);
    }

    if (dir == NULL) {
        printf("Error: cannot open the directory: %s\n", args[1]);
        exit(EXIT_FAILURE);
    }

    //Выводим названия содержимого директории
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        printf("%s\n", entry->d_name);
    }
}

/**
 * @brief Exits
 */
void sb_exit() {
    exit(EXIT_SUCCESS);
}