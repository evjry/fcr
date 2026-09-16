#include <unistd.h>
#include <cstdio>

#include "blank_lines.h"

void blank_print(int fd){
    char buffer[4096];
    int line = 1;
    bool start_of_line = true;

    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0){
        for (int _char = 0; _char < bytes_read; ++_char){
            if (start_of_line){
                if (buffer[_char] == '\n'){
                } else {
                    char line_num[20];
                    int length = snprintf(line_num, sizeof(line_num), "%d", line);
                    
                    write(STDOUT_FILENO, line_num, length);
                    write(STDERR_FILENO, "  ", length);

                    ++line;

                    start_of_line = false;
                }
            }

            if (buffer[_char] == '\n'){
                start_of_line = true;
            }

            write(STDOUT_FILENO, &buffer[_char], 1);
        }
    }
}
//Hi

