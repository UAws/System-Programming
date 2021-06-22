// Author : Akide Liu 
// Date : 21/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>



main() {
     int lspid, morepid, pid;
     int status = 0;
     int fds[2];
     int my_dfs[2];
     int out_pid;

     pipe(fds);
     pipe(my_dfs);

     lspid = fork();
     if(lspid == 0) { /* ls */
         /* Close read end as will not be used */
         // close(fds[0]);
         /* Asign: 1 (stdout) = fds[1] (write end of the pipe) */
         // close(1); dup(fds[1]);
         dup2(fds[1], STDOUT_FILENO);
         /* Close remaining end, otherwise I will not get the EOF */
         close(fds[0]);
         close(fds[1]);
         close(my_dfs[0]);
         close(my_dfs[1]);
         execl("/bin/ls", "ls", "-l", 0);
         exit(-1);
         }

     morepid = fork();
     if(morepid == 0) { /* more */
         /* Close write end as will not be used */
         // close(fds[1]);
         /* Asign: 0 (stdin) = fds[0] (read end of the pipe) */
         // close(STDIN_FILENO); dup(fds[0]);
         //
         dup2(fds[0], STDIN_FILENO);
         dup2(my_dfs[1], STDOUT_FILENO);
         // dup(my_dfs[1]);
         // my_dfs[0] = fds[1];

         close(fds[0]);
         close(fds[1]);
         close(my_dfs[0]);
         close(my_dfs[1]);
         /* Close remaining end, otherwise I will not get the EOF */
         // close(fds[0]);
         // close(my_dfs[1]);

         execl("/bin/more", "more", 0);

         exit(-1);
         }


    pid = fork();
    if (pid == 0){

        printf("out");
        int file_fd = open("out.txt", O_RDWR | O_CREAT, 0644);
        if(file_fd == -1){
            perror("open");
        }

        dup2(my_dfs[0], STDIN_FILENO);
        close(fds[0]);
        close(fds[1]);
        close(my_dfs[0]);
        close(my_dfs[1]);
        dup2(file_fd, STDOUT_FILENO);
        close(file_fd);

        execl("/bin/cat", "cat", 0);
        exit(-1);





    }
     /* Parent closes unused ends */
     close(fds[0]); close(fds[1]);
     close(my_dfs[0]); close(my_dfs[1]);



     /* wait until all children die */
     while((pid = wait(&status)) != -1);

    }