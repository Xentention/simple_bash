#include "main.h"



int main(int argc, char **argv) {
    sb_launch();
}

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


