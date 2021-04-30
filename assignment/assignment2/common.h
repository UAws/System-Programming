// Author : Akide Liu 
// Date : 10/4/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#ifndef SYSTEM_PROGRAMMING_COMMON_H
#define SYSTEM_PROGRAMMING_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "stretchy_buffer.h"
#include "dbg.h"

/*
 This function is used to initialize the two-pointer (**) array and mallocs the required memory for them.
furthermore, this function takes a double pointer array address from the main function and how many numbers of arrays need to be initialized. Then directly modify the array by passing reference.

 va_list , va_start ,va_arg, va_end has been used by following reference : https://codesteps.com/2014/05/16/how-to-pass-variable-number-of-arguments-to-c-cpp-functions/
 */

extern void init_arrays(int num, ...);

/*
 this function used to read input from both argv and file redirection (./main < input file)
fgets used for get input from stdin, after that strokc used for remove \n

The return value of this function is the size of input.
 */

extern int readInput(int argc, char **argv, char **all_commands);

/*
    this function splits all_command from all commands to arguments and commands.

the logic is use strcpy and strcat and use this document as reference : https://gist.github.com/efeciftci/9120921
 */

extern void split_command_argument(char **all_commands, char **arguments, char **commands) ;

/*
 his function takes arguments and commands split from previous func, and current index from for loop inside of main function, to parse the output for execvp
in this function external lib stretchy_buffer.h has been used
 */

extern char ** arguments_to_exec_args(char **arguments, char **commands, int index);


#endif //SYSTEM_PROGRAMMING_COMMON_H
