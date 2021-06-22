// Author : Akide Liu 
// Date : 21/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* command pipeline: cat input1 | tr a-z A-Z | tr \\ q */

int main(void)
{
    int pipe1[2];
    int pipe2[2];
    pid_t pid1;
    char *cmd1[] = { "cat", "test.txt",        0 };
    char *cmd2[] = { "tr",  "a-z",    "A-Z", 0 };
    char *cmd3[] = { "tr",  "A-Z",     "C-ZA-B",   0 };

    if (pipe(pipe1) != 0 || pipe(pipe2) != 0)
    {
        perror("pipe failed");
        return 1;
    }

    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork 1 failed");
        return 1;
    }

    if (pid1 == 0)
    {
        /* Child 1 - cat */
        dup2(pipe1[1], 1);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execvp(cmd1[0], cmd1);
        perror("failed to execute cmd1");
        return 1;
    }

    printf("pid 1 = %d\n", pid1);
    fflush(stdout);

    pid_t pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork 2 failed");
        return 1;
    }

    if (pid2 == 0)
    {
        /* Child 2 - tr a-z A-Z */
        dup2(pipe1[0], 0);
        dup2(pipe2[1], 1);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execvp(cmd2[0], cmd2);
        perror("failed to execute cmd2");
        return 1;
    }

    printf("pid 2 = %d\n", pid2);
    fflush(stdout);

    pid_t pid3 = fork();
    if (pid3 < 0)
    {
        perror("fork 3 failed");
        return 1;
    }

    if (pid3 == 0)
    {
        /* Child 3 - tr \\ q */
        dup2(pipe2[0], 0);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execvp(cmd3[0], cmd3);
        perror("failed to execute cmd3");
        return 1;
    }

    printf("pid 3 = %d\n", pid3);
    fflush(stdout);

    /* Parent - wait for the kids to all die */
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    pid_t corpse;
    int   status;
    while ((corpse = wait(&status)) > 0)
        printf("Child %d died status 0x%.4X\n", corpse, status);

    return 0;
}