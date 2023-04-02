//
// Created by xenia on 20.03.23.
//

#include "parse_lines.h"

/**
 * Reads a line from stdin
 * @return the line
 */
char *read_line(void) {
    char *line = NULL;
    ssize_t bufsize = 0; //выделяем буфер getline

    if (getline(&line, &bufsize, stdin) == -1){
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);  //Дошли до конца файла
        } else  {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

/**
   @brief Split a line into tokens.
   @param line The line.
   @return Null terminated array of tokens.
 */
char **split_line(char *line) {
    int bufsize = SB_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;

    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SB_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += SB_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SB_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

