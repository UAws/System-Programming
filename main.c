#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include "stretchy_buffer.h"

int main() {

    // printf("%s", "4 2020");
    // char *args[] = {"cal", "4", "2020", NULL};
    //
    // execvp("cal", args);


    double *v = 0;
            sb_push(v, 1.0);
            sb_push(v, 42.0);
    for(int i = 0; i < sb_count(v); ++i)
        printf("%g\n", v[i]);
            sb_free(v);
}