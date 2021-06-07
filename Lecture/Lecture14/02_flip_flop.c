#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct point
{
	int x;
	int y;
};

// My crazy flip-flop function
void * flip_flop(void * pt_void_ptr)
{
	// Cast the void pointer back into a struct
	struct point *pt_ptr = (struct point *)pt_void_ptr;

	// While x is less than y, increment x
	while ((*pt_ptr).x < 100)
	{
		if ((*pt_ptr).x  <= (*pt_ptr).y)
		{
			(*pt_ptr).x  = (*pt_ptr).x + 7;
			printf("X is: %d\n", (*pt_ptr).x);
			sleep(1);
		}
	}


	printf("x increment finished... yay!\n");

	// Return NULL (who cares)
	return NULL;
}



int main()
{
	struct point my_point;
	my_point.x = 0;
	my_point.y = 0;

	// Some Printing
	printf("x: %d, y: %d\n", my_point.x, my_point.y);

	// Initialise the thread!!
	pthread_t flip_flop_thread;

	// Run the thread!!
	if(pthread_create(&flip_flop_thread, NULL, flip_flop, &my_point))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	
	// While y is less than x, increment y
	while (my_point.y < 100)
	{
		if (my_point.y <= my_point.x)
		{
			my_point.y = my_point.y + 3;
			printf("Y is: %d\n", my_point.y);
			sleep(1);
		}
	}

	// Rejoin Thread-dom
	if(pthread_join(flip_flop_thread, NULL)) 
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	/* show the results - x is now 100 thanks to the second thread */
	printf("x: %d, y: %d\n", my_point.x, my_point.y);

	return 0;
}
