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


extern void init_arrays(int num, ...);

extern int readInput(int argc, char **argv, char **all_commands);

extern void split_command_argument(char **all_commands, char **arguments, char **commands) ;

extern char ** arguments_to_exec_args(char **arguments, char **commands, int index);


#endif //SYSTEM_PROGRAMMING_COMMON_H
