#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <sys/file.h>


void func(){

	printf("Hello Non-loop\n");
	
	char * arguments[2] = {"./Nothing\0", NULL};

	printf("Hello %s\n", arguments[0]);
	
	int my_exec = execvp(arguments[0], arguments);
	printf("Hello Loop: %d\n", my_exec);

	printf("Hello Loop: test can i print ?");
	printf("Hello Loop: test can i print ?");
	printf("Hello Loop: test can i print ?");
	printf("Hello Loop: test can i print ?");
	//while (1)
	//{
	//	printf("Hello Loop: %d\n", my_exec);
	//}

}


int main()
{
	int id;
	int id2;



	printf("Before Fork\n");
	int i = 0;

	id = fork();
	printf("Fork 1: %d\n", id);
	if (id == 0)
	{
		printf("Child\n");


		id2 = fork();
		printf("Fork 2: %d\n", id2);
		if (id2 > 0)
		{
			printf("Child is now a Parent\n");
			wait(NULL);
		}
		else if  (id2 == 0)
		{
			printf("Grandchild I guess?\n");
		}
		return 0;
	}
	else if (id > 0)
	{
		printf("Parent\n");
		wait(NULL);

	}

}
