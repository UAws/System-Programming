#include "slow_functions.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// How nice of me to include a global that tells you how many commands there were :)
int total_commands = 0;


// ####################################################################################
// ## Please write some code in the following two functions

pthread_cond_t writer_cond;
pthread_cond_t reader_cond;
pthread_mutex_t lock;
int command_index = 0;

/*
 * as the reader and writer are shared same buffer, so that we need classify which thread is in use of this buffer.
 * in the writer we are waiting to condition change (condition is get_written())
 * when we have written 1 we place the wait, and wait for read thread
 * after that write trigger read thread
 *
 * in the read  we are waiting to condition change (condition is get_written())
 * when we have written 0 we place the wait, and wait for write thread
 * after that read trigger write
 */

void * writer(void * in_ptr)
{
    //must include bad_write;

    char **input = (char **) in_ptr;

    for (int i = 0; i < total_commands ; ++i) {

        pthread_mutex_lock(&lock);

        while (get_written() == 1)
        {
            // printf("write wait read !\n");
            pthread_cond_wait(&writer_cond, &lock);
        }
        // writers++;
        // printf("input[%d] = %s\n",command_index,input[command_index]);
        bad_write(input[command_index]);
        command_index++;
        // printf("write trigger read !\n");


        pthread_cond_signal(&reader_cond);
        pthread_mutex_unlock(&lock);
    }


}

void * reader(void * empty)
{

    for (int i = 0; i < total_commands; ++i)
    {
        pthread_mutex_lock(&lock);
        while ((get_written() == 0))
        {
            // printf("read wait write !\n");
            pthread_cond_wait(&reader_cond, &lock);
        }
        // printf("start to read !\n");

        bad_read(empty);

        // writers--;

        // printf("read trigger write !\n");
        pthread_cond_signal(&writer_cond);
        pthread_mutex_unlock(&lock);
    }


    //must include bad_read
}

// ################################################################################
// ## DO NOT MODIFY 

int main()
{

	// ## Parse STDIN and read into commands
	char * commands[100];
	char line[256];
    while (fgets(line, 256, stdin))
    {
		commands[total_commands] = (char*)(malloc(strlen(line) * sizeof(char)));
 		strcpy(commands[total_commands], line);
		total_commands = total_commands + 1;
	}

	pthread_t write1;
	pthread_t read1;

	// Creates a thread which executes writer!
	if(pthread_create(&write1, NULL, writer, commands))
	{
		fprintf(stderr, "Error creating write thread\n");
		return 1;
	}

	// Creates a thread which executes reader!
	if(pthread_create(&read1, NULL, reader, NULL))
	{
		fprintf(stderr, "Error creating read thread\n");
		return 1;
	}

	// Ensure Threads Join Well
	if(pthread_join(write1, NULL)) 
	{
		fprintf(stderr, "Error joining write thread\n");
		return 2;
	}

	if(pthread_join(read1, NULL)) 
	{
		fprintf(stderr, "Error joining read thread\n");
		return 2;
	}

	// Did you really call the right functions?
	get_output();

	// I am a responsible memory user!
	int command_i;
	for (command_i = 0; command_i < total_commands; command_i++)
	{
		free(commands[command_i]);
	}
	return 0;

}
// ## DO NOT MODIFY 
// ################################################################################
