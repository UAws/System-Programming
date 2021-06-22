// Author : Akide Liu 
// Date : 22/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void * doStuff (void *vargp)
{
    sleep(1);
    printf("Do Stuff!\n");
    return NULL;
}

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, doStuff, NULL);
    printf("Main!\n");
    exit(0);
}