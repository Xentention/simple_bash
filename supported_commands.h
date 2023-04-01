//
// Created by xenia on 20.03.23.
//

#ifndef SIMPLE_BASH_SUPPORTED_COMMANDS_H
#define SIMPLE_BASH_SUPPORTED_COMMANDS_H

const char* COMMANDS[] = {
        "help",
        "cd",
        "ls",
        "cat"
};


const char* COMMANDS_INFO[] = {
        "help - information about built-in commands",
        "cd <path> - move to the directory",
        "ls - display a list of files and sub-directories in the current directory",
        "cat <file(s)> - to create, view, concatenate files"
};

#endif //SIMPLE_BASH_SUPPORTED_COMMANDS_H
