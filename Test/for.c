// Author : Akide Liu 
// Date : 18/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

static int anti_cheat = 0;

static pthread_mutex_t lock;

void * slow_function1(void * empty)
{

    system("curl -I 'https://camo.githubusercontent.com/879bc00f178d55ab3c4e576aef08476fce31f5f18ede24e02fccfde0ab51a26f/68747470733a2f2f6b6f6d617265762e636f6d2f67687076632f3f757365726e616d653d416b6964654c6975266c6162656c3d50726f66696c65253230766965777326636f6c6f723d306537356236267374796c653d666c6174'");


    return NULL;
}


int main(int argc, char **argv){



    for (;;) {

        pthread_t * threads = malloc(sizeof(pthread_t) * 10);

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

        free(threads);
    }



    // pthread_mutex_destroy(&lock);
}