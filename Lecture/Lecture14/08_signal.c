#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int global_data;
pthread_cond_t cond;
pthread_mutex_t lock; 

// ## The writing thread is slow
void * writing_thread(void * x_void_ptr)
{
	int count = 0;
	for (count = 0; count < 10; count++)
	{
		sleep(2);
		pthread_mutex_lock(&lock);
		printf("Write Start: %d\n", global_data);
		global_data = global_data + 4;
		pthread_cond_signal(&cond);
		printf("Write End:   %d\n", global_data);
		pthread_mutex_unlock(&lock); 
	}
}

// ## The reading thread is fast
void * reading_thread(void * x_void_ptr)
{
	int thread_id = *((int*)x_void_ptr);
	int count = 0;
	for (count = 0; count < 20; count++)
	{	
		pthread_mutex_lock(&lock);
		printf("Read %d Start:  %d\n", thread_id, global_data);
		if (global_data <= 0)
		{
			pthread_cond_wait(&cond, &lock);
		}
		

		global_data = global_data - 1;
		printf("Read %d End:    %d\n", thread_id, global_data);
		pthread_mutex_unlock(&lock); 
		sleep(1);
	}
}

int main(int argc, char * argv[])
{
	if (argc > 1)
	{


	}

	global_data = 0;

	pthread_t write1;
	pthread_t read1;
	pthread_t read2;

	int read_id1 = 1;
	int read_id2 = 2;

	printf("Here we go\n");

	// create a second thread which executes slow_thread()
	if(pthread_create(&write1, NULL, writing_thread, NULL))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	if(pthread_create(&read1, NULL, reading_thread, &read_id1))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	if(pthread_create(&read2, NULL, reading_thread, &read_id2))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	printf("Main 2\n");


	pthread_exit(NULL);
	return 0;
}
