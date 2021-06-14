#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	char a1[20];
	char a2[20];
	int my_pid;
	my_pid = fork();
	// Child process
	if (my_pid == 0)
	{
		while (1)
		{
			scanf("%s", a1);
			if (a1[0] == 'Q')
			{
				exit(0);
			}
			else
			{
				printf("C Got stuff: %s\n", a1);
			}
		}
		// wait(NULL);
	}
	// Parent
	else if (my_pid > 0)
	{
		while (1)
		{
			scanf("%s", a2);
			if (a2[0] == 'Q')
			{
				exit(0);
			}
			else
			{
				printf("P Got stuff: %s\n", a2);
			}
		}
		wait(NULL);
	}	
	printf("Both: %s, %s\n", a1, a2);
	return 0;
}

