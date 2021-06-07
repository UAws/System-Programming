#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * inc_x(void * x_void_ptr)
{
	// increment x to 10000
	int *x_ptr = (int *)x_void_ptr;
	while(++(*x_ptr) < 10000)
	{
		if (*x_ptr %1000 == 0)
		{
			printf("X is: %d\n", *x_ptr);
			sleep(2);
		}
	}

	printf("x increment finished... yay!\n");

	// There is a return but I don't need it
	return NULL;
}

int main()
{
	int x = 0, y = 0;

	// show the initial values of x and y
	printf("x: %d, y: %d\n", x, y);

	// this variable is our reference to the second thread
	pthread_t inc_x_thread;

	// create a second thread which executes inc_x(&x)
	if (pthread_create(&inc_x_thread, NULL, inc_x, &x))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	// increment y to 100 in the first thread
	while (++y < 10000)
	{
		if (y %1000 == 0)
		{
			printf("Y is: %d\n", y);
			sleep(1);
		}
	}

	printf("y increment finished\n");

	// wait for the second thread to finish
	if(pthread_join(inc_x_thread, NULL)) 
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	// show the results - x is now 100 thanks to the second thread
	printf("x: %d, y: %d\n", x, y);

	return 0;
}
