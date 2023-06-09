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
    (void) signal(SIGINT, SIG_DFL);

    while(1) {
        char cwd[PATH_MAX];
        printf("%s:$$$ ", getcwd(cwd, sizeof(cwd)));
        line = read_line();
        args = split_line(line);
        execute(args);

        free(line);
        free(args);
    }
}


