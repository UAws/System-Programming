#include <stdio.h>
#define array_size 5

int array[array_size];

int sum1(int x[], int dim)
{
	int i;
	int total = 0;

	for (i=0; i < dim; i++)
	{
		total += x[i];
	}
	return total;
}


int sum2(int * x, int dim)
{
	int i;
	int total = 0;

	for (i=0; i < dim; i++)
	{
		total += x[i];
	}
	return total;
}

int sum3(int * x, int dim)
{
	int i;
	int * ptr = x;
	int total = 0;

	for (i=0; i < dim; i++)
	{
		total += *(ptr + i);
	}
	return total;
}

int main(int argc, char ** argv)
{
	int i;
	int * p;
	p = &i;
	for (i=0; i < array_size; i++)
	{
		printf("Please input an integer \n");
		// This is one way
		//scanf("%d", &(array[i]));		
		// This is the other
		scanf("%d", array + i);
	}
	printf("Sum 1: %d\n", sum1(array, array_size));
	printf("Sum 2: %d\n", sum2(array, array_size));
	printf("Sum 3: %d\n", sum3(array, array_size));
	
}
