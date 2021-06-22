// Author : Akide Liu 
// Date : 21/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int readInput(int argc, char **argv, char **all_commands){

    int fd;

    int all_commands_index = 0;

    // put stdin input into all_commands

    close(0); // Close stdin

    fd = open(argv[1],O_RDONLY);

    if (fd != 0) {
        fprintf(stderr, "could not open data as fd 0\n");
        exit(1);
    }

    while (fgets(all_commands[all_commands_index], 256, stdin) != NULL) {

        // remove \n
        all_commands_index++;

    }


    return all_commands_index;

}

int main(int argc, char **argv){


    char **all_commands = (char **) malloc(sizeof(char *) * 256);

    for (int i = 0; i < 256; ++i) {
        all_commands[i] = (char *) malloc(sizeof(char) * 256);
    }

    int result = readInput(argc, argv, all_commands);

    printf("%d", result);

    for (int i = 0; i < 256; ++i) {
        free(all_commands[i]);
    }

    free(all_commands);

}