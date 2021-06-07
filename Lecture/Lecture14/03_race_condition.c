#include <stdio.h>
#include <pthread.h>

void * inc_x(void * x_void_ptr)
{
	/* increment x to 100 */
	int *x_ptr = (int *)x_void_ptr;

	int in_thread = 0;
	while((*x_ptr) < 100000000)
	{
		(*x_ptr) = (*x_ptr) + 1;
		in_thread = in_thread + 1;
	}	

	printf("In  Thread: %d\n", in_thread);

	/* the function must return something - NULL will do */
	return NULL;
}

int main()
{
	int x = 0;

	/* show the initial values of x and y */
	printf("x: %d\n", x);

	/* this variable is our reference to the second thread */
	pthread_t inc_x_thread;

	/* create a second thread which executes inc_x(&x) */
	if(pthread_create(&inc_x_thread, NULL, inc_x, &x))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	/* increment y to 100 in the first thread */
	int out_thread = 0;
	while(x < 100000000)
	{
		x = x + 1;
		out_thread = out_thread + 1;
	}

	printf("Out Thread: %d\n", out_thread);

	/* wait for the second thread to finish */
	if(pthread_join(inc_x_thread, NULL)) 
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	/* show the results - x is now 100 thanks to the second thread */
	printf("x: %d\n", x);

	return 0;
}
