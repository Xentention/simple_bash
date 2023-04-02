//
// Created by xenia on 20.03.23.
//

#ifndef SIMPLE_BASH_PARSE_LINES_H
#define SIMPLE_BASH_PARSE_LINES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SB_BUFSIZE 64
#define SB_DELIM " \t\r\n\a"

char *read_line(void);
char **split_line(char *line);

#endif //SIMPLE_BASH_PARSE_LINES_H
