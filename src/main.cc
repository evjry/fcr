#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <vector>
#include <errno.h>

#include "include/num_lines.h"
#include "include/blank_lines.h"
#include "include/show_ends.h"

int main(int argc, char **argv){
    int arg = 1;
    char buffer[4096];
    ssize_t bytes_read;

    bool num_lines = false;
    bool blank_lines = false;
    bool show_ends = false;
    bool rstring = false;

    //if (argc < 2){
    //    std::cout << "fcr: " << std::endl;
    //    std::cout << "-n [Number all lines]" << std::endl;
    //    std::cout << "-b [Number all non-blank lines]" << std::endl;
    //    std::cout << "-e [Show end of each line by printing $ sign]" << std::endl;
    //    return 0;
    //}
    
    if (argc == 1){
        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0){
            write(STDOUT_FILENO, buffer, bytes_read);
            return 0;
        }
    }
    if (std::string(argv[arg]) == "-"){
        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0){
            write(STDOUT_FILENO, buffer, bytes_read);
            return 0;
        }   
    }

    // going through each command argument.
    // starting with 1, because 0 argument is the command name.
    for (int arg = 1; arg < argc; ++arg){
        if (std::string(argv[arg]) == "-n"){
            num_lines = true;
            continue;
        }
        if (std::string(argv[arg]) == "-b"){
            blank_lines = true;
            continue;
        }
        if (std::string(argv[arg]) == "-e"){
            show_ends = true;
            continue;
        }

        int rf = open(argv[arg], O_RDONLY);

        if (rf == -1){
            perror("fcr");
            continue;
        }

        if (num_lines){num_print(rf);}
        if (blank_lines){blank_print(rf);}
        if (show_ends){end_print(rf);}

        while ((bytes_read = read(rf, buffer, sizeof(buffer))) > 0){
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        std::cout << std::endl;
        close(rf);
    }
    return 0;
}