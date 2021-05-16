// Author : Akide Liu 
// Date : 10/5/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description :

/**  smsh2.c  small-shell version 2
 **		first really useful version after prompting shell
 **		this one parses the command line into strings
 **		uses fork, exec, wait, and ignores signals
 **/

//

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	"smsh.h"
#include "dbg.h"
#include "stretchy_buffer.h"

#define	DFL_PROMPT	"> "



int main()
{
    char	*cmdline, *prompt, **arglist;
    int	result;
    void	setup();

    prompt = DFL_PROMPT ;
    setup();

    while ( (cmdline = next_cmd(prompt, stdin)) != NULL ){
        if ( (arglist = splitline(cmdline)) != NULL  ){

            // REMOVABLE : debug

            // dbg(cmdline);
            // for (int i = 0; arglist[i] != NULL; ++i) {
            //     dbg(arglist[i]);
            // }


            // input : ls -l | wc -c
            /*
            > ls -l | wc -c
            > /Users/akide/CLionProjects/System Programming/assignment/assignment3/smsh2.c:69: (main) cmdline = "ls -l | wc -c"
            /Users/akide/CLionProjects/System Programming/assignment/assignment3/smsh2.c:71: (main) arglist[i] = "ls"
            /Users/akide/CLionProjects/System Programming/assignment/assignment3/smsh2.c:71: (main) arglist[i] = "-l"
            /Users/akide/CLionProjects/System Programming/assignment/assignment3/smsh2.c:71: (main) arglist[i] = "|"
            /Users/akide/CLionProjects/System Programming/assignment/assignment3/smsh2.c:71: (main) arglist[i] = "wc"
            /Users/akide/CLionProjects/System Programming/assignment/assignment3/smsh2.c:71: (main) arglist[i] = "-c"
             */


            result = execute(arglist);

            freelist(arglist);
        }
        free(cmdline);
    }
    return 0;
}

void setup()
/*
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
    signal(SIGINT,  SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
    fprintf(stderr,"Error: %s,%s\n", s1, s2);
    exit(n);
}
