// Author : Akide Liu 
// Date : 10/5/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include <string.h>
#include <fcntl.h>  // For open

int main(int argc,char *argv[]) {

    char *argument1[] = {"ls", NULL, NULL};
    char *argument2[] = {"wc", NULL, NULL};
    int fd[2];
    pid_t cpid;
    close(1); /* so that output file should get file descriptor 1 */
    int file_dsptr = open(argv[3],O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); /* file should be exist in current directory, otherwise use O_CREAT | O_TRUNC */
    printf("[%d]\n",file_dsptr);

    if(argc == 4){
        if(pipe(fd) == -1){
            perror("error in pipe creation");
            exit(EXIT_FAILURE);
        }
        cpid = fork();
        if( cpid == 0 ){ /*child process */
            close( fd[0] ); /* close read end of pipe */
            if( -1 == dup2(fd[1] , file_dsptr)){ /* duplicate fd[1] to fd where data.txt points */
                exit( EXIT_FAILURE );
            }
            // if(-1 == execlp(argv[1] , argv[1] , NULL )){ /* executes the commands */
            if(-1 == execvp(argv[1] , argument1 )){ /* executes the commands */
                exit( EXIT_FAILURE );
            }
            close( fd[1] );
            _exit( EXIT_SUCCESS );
        }
        else if(cpid > 0){
            wait( NULL ); /* wait for child to completes */
            close( fd[1] ); /* close write end of pipe */
            if( -1 == dup2(fd[0] , STDIN_FILENO)) {
                exit( EXIT_FAILURE );
            }
            // if(-1 == execlp(argv[2] , argv[2], NULL )) {
            if(-1 == execvp(argv[2] , argument2)) {
                exit( EXIT_FAILURE );
            }
            close( fd[0] );
            _exit( EXIT_SUCCESS );
        }
        else{
            fprintf(stderr, "fork failed\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        fprintf(stderr, "Usage Msg :. ./a.out ls wc data.txt \n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
