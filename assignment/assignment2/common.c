// Author : Akide Liu 
// Date : 10/4/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include "common.h"

int readInput(int argc, char **argv, char **all_commands){

    int all_commands_index = 0;

    // put stdin input into all_commands

    while (fgets(all_commands[all_commands_index], 256, stdin) != NULL) {

        // remove \n
        strtok(all_commands[all_commands_index], "\n");

        all_commands_index++;

    }

    //put command line arguments into all_commands;

    int i ;
    for (i = 1; i <= argc; ++i) {

        all_commands[all_commands_index] = argv[i];

        all_commands_index++;

    }

    return all_commands_index - 1;

}

void split_command_argument(char **all_commands, char **arguments, char **commands) {

    // https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

    int i;
    for (i = 0; all_commands[i] != NULL; ++i) {

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

    int j;
    for (j = 0; j < num; ++j) {

        // https://stackoverflow.com/a/5845702/14207562
        // malloc-ating multidimensional array in function

        char ***temp_arrays = va_arg(valst, char***);

        // C 2D array with length 256 for ALL all_commands include maximum 100 from file and 10 max from arguments

        *temp_arrays = (char **) malloc(sizeof(char *) * (100 + 10));

        int i;
        for (i = 0; i < 110; ++i) {

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

