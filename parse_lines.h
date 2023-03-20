//
// Created by xenia on 20.03.23.
//

#ifndef SIMPLE_BASH_PARSE_LINES_H
#define SIMPLE_BASH_PARSE_LINES_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "supported_commands.h"

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char *read_line(void);
char **split_line(char *line);

#endif //SIMPLE_BASH_PARSE_LINES_H
