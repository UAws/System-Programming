/* execute.c - code used by small shell to execute commands */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include "stretchy_buffer.h"
#include <string.h>
#include "dbg.h"
#include <fcntl.h>  // For open




/*
 * ---------------------------------------------------------------------------
 *
 * important : for style and general standard of code please refer execute4.c
 *
 * ---------------------------------------------------------------------------
 */

// for part 1
char **arguments_to_exec_args(char *const *argv, char *const *commands, int i);

// for part 2
void redirection_io_handler(char **argv, char **commands);

void redirection_in(char *argv[], char **commands);

int execute(char *argv[])
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors

 */
{

    int  redirection_flag = 0;
    int pipe_flag = 0;

    char ** commands = NULL;

    if (argv[0] != NULL) {
        sb_push(commands, argv[0]);
    }
    for (int i = 1; argv[i] != NULL; ++i) {
        if ((strcmp(argv[i], "|")) == 0) {
            sb_push(commands, argv[i + 1]);
        }

        if ((strcmp(argv[i], "<")) == 0 || (strcmp(argv[i], ">")) == 0) {
             redirection_flag ++;
        }

    }


    int	pid ;
    int	child_info = -1;

    int my_pipe[2];
    int prev_pipe;

    int fd1;
    int fd2;

    if ( redirection_flag != 1) {
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



                // dbg(commands[i]);
                // for (int j = 0; j < sb_count(arguments); ++j) {
                //     dbg(arguments[j]);
                // }

                // dbg(sb_count(arguments));

                int tmp_flag = 0;
                for (int j = 0; j < sb_count(arguments); ++j) {

                    // dbg(arguments[j]);
                    if (arguments[j] != NULL) {
                        if (strstr(arguments[j],">") != NULL) {

                            tmp_flag+=1;

                        }
                    }

                }



                signal(SIGINT, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);

                // dbg(tmp_flag);
                if (tmp_flag == 0) {

                    // dbg("pipe no redirection");

                    execvp(commands[i], arguments);

                }else{

                    // dbg("pipe + redirection");
                    redirection_in(argv, commands);
                    redirection_io_handler(argv, commands);
                }
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

    } else {

        redirection_io_handler(argv, commands);
        redirection_in(argv, commands);

    }



    return child_info;
}

void redirection_io_handler(char **argv, char **commands) {

    for (int i = 0; i < sb_count(commands); ++i) {

        // dbg(sb_count(commands));

        char **arguments = arguments_to_exec_args(argv, commands, i);


        for (int j = 0; j < sb_count(arguments) - 1; ++j) {

            if (strcmp(arguments[j],">") == 0) {

                // dbg("out");

                int exit_value;
                int output = dup(STDOUT_FILENO);
                int file_fd = open(sb_last(arguments), O_RDWR | O_CREAT, 0644);
                if(file_fd == -1){
                    perror("open");
                }
                dup2(file_fd, STDOUT_FILENO);

                arguments[sb_count(arguments)-2] = NULL;
                        sb_last(arguments) = NULL;


                //fork child process
                pid_t pid;
                pid = fork();
                if (pid == -1) {
                    perror("fork");
                } else if(pid == 0) {

                    signal(SIGINT, SIG_DFL);
                    signal(SIGQUIT, SIG_DFL);

                    execvp(commands[i], arguments);
                    perror("execvp");
                    exit(1);
                }
                wait(&exit_value);
                dup2(output, STDOUT_FILENO);
                close(output);
                close(file_fd);
            }
        }

    }

}


void redirection_in(char *argv[], char **commands) {

    for (int i = 0; i < sb_count(commands); ++i) {

        // dbg(sb_count(commands));

        char **arguments = arguments_to_exec_args(argv, commands, i);

        for (int j = 0; j < sb_count(arguments) - 1; ++j) {

            if (strcmp(arguments[j], "<") == 0) {

                // dbg("in");

                int exit_value;
                int input = dup(STDIN_FILENO);

                int file_fd = open(sb_last(arguments), O_RDONLY);
                if (file_fd == -1) {
                    perror("open");
                }
                dup2(file_fd, STDIN_FILENO);

                arguments[sb_count(arguments)-2] = NULL;
                sb_last(arguments) = NULL;


                pid_t pid;
                pid = fork();
                if (pid == -1) {
                    perror("fork");
                } else if (pid == 0) {

                    signal(SIGINT, SIG_DFL);
                    signal(SIGQUIT, SIG_DFL);

                    // for (int k = 0; k < sb_count(arguments); k++) {
                    //     dbg(arguments[k]);
                    // }

                    execvp(commands[i], arguments);
                    perror("execvp");
                    exit(1);
                }
                wait(&exit_value);
                dup2(input, STDIN_FILENO);
                close(input);
                close(file_fd);
            }
        }
    }

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
