// Author : Akide Liu 
// Date : 7/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "slow_functions.h"


/*
 * as the we required that slow_function1 to print 'work done', do that we need modify
 * the static variable 'special' to larger than 9 and not larger than 10 which is 10
 * as the slow_function1 sleep 1 second on one thread run,
 * so we could promote 10 threads running slow_function1 asynchronously
 * in order to increase the 'special' to 10 between 1 second and 2 second.
 * After slow_function2 sleep 2 second the function print End 2.
 */

int main(int argc, char **argv){


    pthread_t * threads = malloc(sizeof(pthread_t) * 10);

    pthread_t func_2_thread;

    if (pthread_create(&func_2_thread, NULL, slow_function2, NULL))
    {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    for (int i = 0; i < 10; ++i) {
        if (pthread_create(&threads[i], NULL, slow_function1, NULL))
        {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    for (int i = 0; i < 10; ++i) {
        if(pthread_join(threads[i], NULL))
        {
            fprintf(stderr, "Error joining thread\n");
            return 2;
        }
    }

    if(pthread_join(func_2_thread, NULL))
    {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    // pthread_mutex_destroy(&lock);
}