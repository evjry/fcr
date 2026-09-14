#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <vector>

#include "include/num_lines.h"
#include "include/blank_lines.h"

int main(int argc, char **argv){
    bool num_lines = false;
    bool blank_lines = false;

    // checking if command has any argument.
    if (argc < 2){
        std::cout << "fcr: " << std::endl;
        std::cout << "-n [Number all lines]" << std::endl;
        std::cout << "-b [Number all non-blank lines]" << std::endl;
        return 0;
    }

    // going through each command argument.
    // starting with 1, because 0 argument is the command name.
    for (int arg = 1; arg < argc; ++arg){
        char buffer[4096];
        ssize_t bytes_read;

        if (std::string(argv[arg]) == "-n"){
            num_lines = true;
            continue;
        }
        if (std::string(argv[arg]) == "-b"){
            blank_lines = true;
            continue;
        }

        int rf = open(argv[arg], O_RDONLY);

        if (rf == -1){
            std::cerr << "Error: fcr couldnt open " << argv[arg] << '\n';
            continue;
        }

        if (num_lines){num_print(rf);}
        if (blank_lines){blank_print(rf);}
        
        while ((bytes_read = read(rf, buffer, sizeof(buffer))) > 0){
            //output everything that was in bytes_read
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        std::cout << std::endl;
        close(rf);
    }
    return 0;
}