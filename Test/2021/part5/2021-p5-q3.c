// Author : Akide Liu 
// Date : 22/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char **argv){
    char * command[2] = {"wc", "test_file"};
    int pid = fork();			// Explain
    if (pid < 0) {
        // handle_error();
    }
    else if (pid > 0) {
        wait(NULL);			// Explain
    }
    else {
        execvp(command[0], command);	// Explain
    }
    printf("Complete\n");			// Last line
}