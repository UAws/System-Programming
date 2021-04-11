// Author : Akide Liu 
// Date : 31/3/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include "common.h"

int main(int argc, char **argv){

    char **commands;
    char **arguments;
    char **all_commands;

    init_arrays(3,&commands, &arguments, &all_commands);

    // while there are remaining commands:
    //     read line from file
    readInput(argc, argv, all_commands);

    //  parse line into command and arguments
    split_command_argument(all_commands, arguments, commands);

    // https://ece.uwaterloo.ca/~dwharder/icsrts/Tutorials/fork_exec/

    // for cmd in commands:
    int i;
    for (i = 0; all_commands[i] != NULL; ++i) {

        //     fork and handle errors
        int pid = fork();

        if (pid < 0) {

            perror("Fork failed");

        }

        if (pid == 0) {

            //         execute command
            char ** exec_argv = arguments_to_exec_args(arguments,commands,i);

            // REMOVABLE : debug
            // dbg(i);
            // dbg(exec_argv[i]);
            // dbg(arguments[i]);
            // dbg(commands[i]);

            execvp(commands[i], exec_argv);

            sb_free(exec_argv);


        } else {

            // wait for child to terminate
            wait(NULL);

        }

    }

    // close any remaining pipes, clean up
    free(commands);
    free(arguments);
    free(all_commands);

    return 0;

}
