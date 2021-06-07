#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void * boring_thread(void * x_void_ptr)
{
	int k = 0;
	while(k < 5)
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
	int do_exit = 0;
	if (argc > 1)
	{
		printf("%s\n", argv[1]);
		if (strcmp(argv[1], "Join") == 0)
		{
			printf("Join\n");
			do_join = 1;
		}
		else if (strcmp(argv[1], "Exit") == 0)
		{
			printf("Exit\n");
			do_exit = 1;
		}

	}
	// this variable is our reference to the second thread
	pthread_t attr_thread_ptr;
	pthread_attr_t my_attr;

	pthread_attr_init(&my_attr);
	pthread_attr_setdetachstate(&my_attr, PTHREAD_CREATE_DETACHED);

	printf("Main 1\n");

	// create a second thread which executes slow_thread()
	if(pthread_create(&attr_thread_ptr, &my_attr, boring_thread, NULL))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	printf("Main 2\n");


	// wait for the second thread to finish
	if (do_join)
	{
		if(pthread_join(attr_thread_ptr, NULL)) 
		{
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
	}
	printf("Main 3\n");

	if (do_exit)
	{
		pthread_exit(NULL);
	}
	return 0;
}
