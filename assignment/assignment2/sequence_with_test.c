// Author : Akide Liu 
// Date : 31/3/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "stretchy_buffer.h"


void init_arrays(int num, ...);

void readInput(int argc, char **argv, char **all_commands);

void split_command_argument(char **all_commands, char **arguments, char **commands) ;

char ** arguments_to_exec_args(char **arguments, char **commands, int index);

int main(int argc, char **argv){

    char **commands;
    char **arguments;
    char **all_commands;

    init_arrays(3,&commands, &arguments, &all_commands);

    readInput(argc, argv, all_commands);

    split_command_argument(all_commands, arguments, commands);

    // printf("%d", (int)strlen(all_commands));

    // // testing
    // for (int i = 0; all_commands[i] != NULL; ++i) {
    //
    //     printf("%s", commands[i]);
    //
    //     printf(" %s\n", arguments[i]);
    //
    //
    // }

    // https://ece.uwaterloo.ca/~dwharder/icsrts/Tutorials/fork_exec/

    for (int i = 0; all_commands[i] != NULL; ++i) {

        // printf("current_arg : %s \n",arguments[i]);
        int pid = fork();

        if (pid == 0) {

            char ** exec_argv = arguments_to_exec_args(arguments,commands,i);

            execvp(commands[i], exec_argv);

            sb_free(exec_argv);


        } else {

            wait(NULL);

        }

    //
    }






    free(commands);
    free(arguments);
    free(all_commands);

    return 0;

}

void readInput(int argc, char **argv, char **all_commands){

    int all_commands_index = 0;

    // put stdin input into all_commands

    while (fgets(all_commands[all_commands_index], 256, stdin) != NULL) {

        // remove \n
        strtok(all_commands[all_commands_index], "\n");

        all_commands_index++;

        // printf("%s", *all_commands);
    }

    //put command line arguments into all_commands;

    for (int i = 1; i <= argc; ++i) {

        all_commands[all_commands_index] = argv[i];

        all_commands_index++;

    }



    // testing
    /**
    for (int i = 0; all_commands[i] != NULL; ++i) {

        printf("%s", all_commands[i]);

    }
    */

}

void split_command_argument(char **all_commands, char **arguments, char **commands) {

    // https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

    for (int i = 0; all_commands[i] != NULL; ++i) {

        // https://gist.github.com/efeciftci/9120921

        char *word;
        word = strtok(all_commands[i], " ");
        strcpy(commands[i], word);

        while ((word = strtok(NULL, " ")) != NULL) {
            strcat(arguments[i], word);
            strcat(arguments[i]," ");
        }

    }

}

// https://codesteps.com/2014/05/16/how-to-pass-variable-number-of-arguments-to-c-cpp-functions/

void init_arrays(int num, ...){

    va_list valst;

    va_start(valst, num);

    for (int j = 0; j < num; ++j) {

        // https://stackoverflow.com/a/5845702/14207562
        // malloc-ating multidimensional array in function

        char ***temp_arrays = va_arg(valst, char***);

        // C 2D array with length 256 for ALL all_commands include maximum 100 from file and 10 max from arguments

        *temp_arrays = (char **) malloc(sizeof(char *) * (100 + 10));


        for (int i = 0; i < 110; ++i) {

            // C array with length 256 for current line ;

            (*temp_arrays)[i] = (char *) malloc(sizeof(char) * 256);

        }
    }


    va_end(valst);



}


char ** arguments_to_exec_args(char **arguments, char **commands, int index) {

    char **result = NULL;

    sb_push(result,commands[index]);



    if (strlen(arguments[index]) != 0) {

        char* word;

        word = strtok(arguments[index], " ");

        sb_push (result, word);

        while ((word = strtok(NULL, " ")) != NULL){

            sb_push(result,word);

        }


    } else {

        sb_push(result, NULL);

    }

    sb_push(result,NULL);


    return result;

}

