//
// Created by xenia on 20.03.23.
//

#include "main.h"

int main() {
    sb_launch();
}

/**
 * @brief Launches the shell
 */
_Noreturn void sb_launch(){
    char *line;
    char **args;
    (void) signal(SIGINT, sb_kill);

    while(1) {
        printf("$$$ ");
        line = read_line();
        args = split_line(line);
        execute(args);

        free(line);
        free(args);
    }
}


