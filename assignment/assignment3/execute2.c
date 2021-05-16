/* execute.c - code used by small shell to execute commands */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include "stretchy_buffer.h"
#include <string.h>
#include "dbg.h"


/*
 * ---------------------------------------------------------------------------
 *
 * important : for style and general standard of code please refer execute4.c
 *
 * ---------------------------------------------------------------------------
 */

// for part 1
char **arguments_to_exec_args(char *const *argv, char *const *commands, int i);

int execute(char *argv[])
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors

 */
{


    char ** commands = NULL;

    if (argv[0] != NULL) {
        sb_push(commands, argv[0]);
    }
    for (int i = 1; argv[i] != NULL; ++i) {
        if ((strcmp(argv[i], "|")) == 0) {
            sb_push(commands, argv[i + 1]);
        }
    }

    // for (int i = 0; commands[i] != NULL; ++i) {
    //     dbg(commands[i]);
    // }

	int	pid ;
	int	child_info = -1;
    int my_pipe[2];
    int prev_pipe;
    // dbg(sb_count(commands));
    for (int i = 0; i < sb_count(commands); ++i) {

        // if this is not the final command:
        // pipe (new_pipe)
        // Create a new pipe
        if (i != sb_count(commands) - 1) {
            if (pipe(my_pipe) == -1) {
                perror("Cannot create pipe\n");
            }
        }



        if ( argv[0] == NULL )		/* nothing succeeds	*/
            return 0;

        if ( (pid = fork())  == -1 )
            perror("fork");
        else if ( pid == 0 ){

            //  if this is not the first command:
            //  Redirect input to prev_pipe
            if (i != 0) {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            // if this is not the final command:
            // Redirect output to new_pipe
            if (i != sb_count(commands) - 1) {
                dup2(my_pipe[1], STDOUT_FILENO);
                close(my_pipe[1]);
            }


            char **arguments = arguments_to_exec_args(argv, commands, i);


            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);

            // dbg(commands[i]);
            // for (int j = 0; j < sb_count(arguments); ++j) {
            //     dbg(arguments[j]);
            // }

            execvp(commands[i], arguments);
            sb_free(arguments);
            perror("cannot execute command");
            exit(1);
        }
        else {
            // if this is not the first command:
            // close prev_pipe
            if (i != 0) {
                close(prev_pipe);
            }

            // if this is not the final command:
            // prev_pipe = new_pipe
            if (i != sb_count(commands) - 1) {
                prev_pipe = my_pipe[0];
                close(my_pipe[1]);
            }

            if ( wait(&child_info) == -1 )
                perror("wait");
        }

    }

	return child_info;
}

char **arguments_to_exec_args(char *const *argv, char *const *commands, int i) {
    char ** arguments = NULL;
    bool push_argument_flag = false;

    sb_push(arguments, commands[i]);


    if (argv[1] == NULL) {
        sb_push(arguments, NULL);
    } else {
        for (int j = 0; argv[j] != NULL; ++j) {


            // if there are not arguments, push null and immediately break
            if (argv[j + 1] != NULL) {
                if ((strcmp(argv[j + 1], "|")) == 0 && (strcmp(argv[j], commands[i])) == 0) {
                    push_argument_flag = false;
                    sb_push(arguments, NULL);
                    break;
                }
            }



            // start push next string into arguments
            if ((strcmp(argv[j], commands[i])) == 0) {
                push_argument_flag = true;
                j++;

                // stop pushing
            } else if ((strcmp(argv[j], "|")) == 0 && push_argument_flag == true) {
                push_argument_flag = false;
                break;
            }

            // pushing string
            if (push_argument_flag) {
                sb_push(arguments, argv[j]);
            }

        }
    }

    if (sb_count(arguments) < 3) {
        for (int j = 0; j <= 3 - sb_count(arguments); ++j) {
                    sb_push(arguments, NULL);
        }
    }
    return arguments;
}
