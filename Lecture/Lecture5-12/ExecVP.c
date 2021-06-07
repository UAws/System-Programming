#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
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

	return 0;
}
