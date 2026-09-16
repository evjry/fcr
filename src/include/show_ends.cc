#include <unistd.h>
#include <cstdio>

#include <string>

#include "blank_lines.h"

void end_print(int fd){
    char buffer[4096];
    bool end_of_line = false;
    bool comment = false;

    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0){
        for (int _char = 0; _char < bytes_read; ++_char){
            if (buffer[_char] == '\n'){
                end_of_line = true;
            }

            if (end_of_line){
                char line_end[20];
                write(STDOUT_FILENO, "$", 2);
                end_of_line = false;
            }
            write(STDOUT_FILENO, &buffer[_char], 1);
        }
    }
}