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

    // initialize all double pointer array use malloc

    init_arrays(3,&commands, &arguments, &all_commands);

    // while there are remaining commands:
    //     read line from file
    int input_length = readInput(argc, argv, all_commands);

    //  parse line into command and arguments

    split_command_argument(all_commands, arguments, commands);

    // https://ece.uwaterloo.ca/~dwharder/icsrts/Tutorials/fork_exec/


    int my_pipe[2];

    int prev_pipe;

    // dbg(input_length);
    int i;

    for (i = 0; i < input_length; ++i) {

        // if this is not the final command:
        // pipe (new_pipe)
        // Create a new pipe
        if (i != input_length - 1) {
            if (pipe(my_pipe) == -1) {
                perror("Cannot create pipe\n");
            }
        }

        // dbg(all_commands[i]);


        // fork and handle errors
        int pid = fork();

        if (pid < 0) {

            perror("Fork failed");

        }

        // Child
        if (pid == 0) {

            //  if this is not the first command:
            //  Redirect input to prev_pipe
            if (i != 0) {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            // if this is not the final command:
            // Redirect output to new_pipe
            if (i != input_length - 1) {
                dup2(my_pipe[1], STDOUT_FILENO);
                close(my_pipe[1]);
            }

            // execute command
            char ** exec_argv = arguments_to_exec_args(arguments,commands,i);

            // REMOVABLE : debug
            // dbg(i);
            // dbg(exec_argv[i]);
            // dbg(arguments[i]);
            // dbg(commands[i]);

            execvp(commands[i], exec_argv);


            sb_free(exec_argv);

        // Parent
        }
        else {
            // if this is not the first command:
            // close prev_pipe
            if (i != 0) {
                close(prev_pipe);
            }

            // if this is not the final command:
            // prev_pipe = new_pipe
            if (i != input_length - 1) {
                prev_pipe = my_pipe[0];
                close(my_pipe[1]);
            }

            wait(NULL);
        }

    }


    // close any remaining pipes, clean up
    for (i = 0; i < input_length; ++i) {
        close(my_pipe[i]);
    }



    free(commands);
    free(arguments);
    free(all_commands);
}
