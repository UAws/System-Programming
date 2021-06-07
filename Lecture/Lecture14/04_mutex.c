#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int global_x = 0;
pthread_mutex_t lock; 

void * inc_x(void * in_void_flag)
{
	int * flag = (int *) in_void_flag; 
	while(1)
	{
		// Mutex OFF
		if (*flag == 1)
		{
			pthread_mutex_lock(&lock); 
		}
	
		// Print
		if (global_x >= 20)
		{
			// Mutex OFF
			if (*flag == 1)
			{
				pthread_mutex_unlock(&lock); 
			}
			return NULL;
		}

		int temp_x = global_x;
		temp_x = temp_x + 1;
		sleep(0.05);
		global_x = temp_x;	
		printf("X is: %d\n", global_x);
		
		

		// Mutex OFF
		if (*flag == 1)
		{
			pthread_mutex_unlock(&lock); 
		}

	}

	//printf("X increment finished... yay!\n");

	// There is a return but I don't need it
	return NULL;
}

int main(int argc, char * argv[])
{

	// Initialise Mutex
	int mutex_flag = 0;
	if (argc > 1)
	{
		mutex_flag = 1;
	}

	// Initialise an array of threads
	pthread_t * threads = malloc(sizeof(pthread_t) * 10);

	if (pthread_mutex_init(&lock, NULL) != 0) 
	{ 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 

	// Start 10 Threads
	for (int count = 0; count < 10; count++) 
	{
		if(pthread_create(&threads[count], NULL, inc_x, &mutex_flag))
		{
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}
	}

	// Join 10 Threads
	for (int count = 0; count < 10; count++) 
	{
		if(pthread_join(threads[count], NULL)) 	
		{
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
	}

	// Destroy Mutex
	pthread_mutex_destroy(&lock); 
	return 0;
}
