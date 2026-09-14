#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <vector>

int main(int argc, char **argv){
    // checking if command has any argument.
    if (argc < 2){
        return 0;
    }

    // going through each command argument.
    // starting with 1, because 0 argument is the command name.
    for (int i = 1; i < argc; ++i){
        int rf = open(argv[i], O_RDONLY);

        if (rf == -1){
            std::cerr << "Error: fcr couldnt open " << argv[i] << '\n';
            continue;
        }

        char buffer[4096];
        ssize_t bytes_read;
        
        //while read up to 4096 bytes at a time from the file(s)
        //and keep reading until there's nothing left.
        while ((bytes_read = read(rf, buffer, sizeof(buffer))) > 0){
            //write standartOUT_FILENO, buffer(get characters out of buffer, bytes_read)
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        std::cout << std::endl;
        close(rf);
    }
    return 0;
}