#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void * slow_thread(void * x_void_ptr)
{
	int k = 0;
	while(k < 2)
	{
		printf("k is %d\n", k);
		sleep(1);
		k++;
	}
	return NULL;
}

int main(int argc, char * argv[])
{
	int do_join = 0;

	if (argc > 1)
	{
		if (strcmp(argv[1], "Join") == 0)
		{
			printf("Join\n");
			do_join = 1;
		}
	}

	// this variable is our reference to the second thread
	pthread_t slow_thread_ptr;

	// create a second thread which executes slow_thread()
	if(pthread_create(&slow_thread_ptr, NULL, slow_thread, NULL))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	pthread_detach(slow_thread_ptr);

	printf("Hello World\n");

	int j = 0;
	while(j < 6)
	{
		printf("j is %d\n", j);
		sleep(1);
		j++;
	}

	// wait for the second thread to finish
	if(do_join && pthread_join(slow_thread_ptr, NULL)) 
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	printf("Goodbye World\n");

	return 0;
}
