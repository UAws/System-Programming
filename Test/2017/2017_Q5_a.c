// Author : Akide Liu 
// Date : 22/6/21
// License and copyright notice: GNU General Public License v3.0 
// https://www.gnu.org/licenses/gpl-3.0.en.html
// Description : 

//


#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>
struct arg_set {
    char *fname;
    int count;
};
struct arg_set *mailbox = NULL;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t flag = PTHREAD_COND_INITIALIZER;
main(int ac, char *av[])
{
    pthread_t t1, t2;
    struct arg_set args1, args2;
    void *count_words(void *);
    int reports_in = 0;
    int total_words = 0;
    if ( ac != 3 ){
        printf("usage: %s file1 file2\n", av[0]);
        exit(1);
    }
    pthread_mutex_lock(&lock);
    //MARKER1
    args1.fname = av[1];
    args1.count = 0;
    pthread_create(&t1, NULL, count_words, (void *) &args1);
    args2.fname = av[2];
    args2.count = 0;
    pthread_create(&t2, NULL, count_words, (void *) &args2);
    //MARKER2
    while( reports_in < 2 ){
        pthread_cond_wait(&flag, &lock);
        total_words += mailbox->count;
        if ( mailbox == &args1)
            pthread_join(t1,NULL);
        if ( mailbox == &args2)
            pthread_join(t2,NULL);
        mailbox = NULL;
        pthread_cond_signal(&flag);
        reports_in++;
    }
//MARKER3
    printf("%7d: total words\n", total_words);
}
void *count_words(void *a)
{
    struct arg_set *args = a;
//code to open a file of filename given in args
// and then count words in the file
// here
//MARKER4
    pthread_mutex_lock(&lock);
    while ( mailbox != NULL ){
        pthread_cond_wait(&flag,&lock);
    }
//MARKER5
    mailbox = args;
    pthread_cond_signal(&flag);
    pthread_mutex_unlock(&lock);
    return NULL;
}