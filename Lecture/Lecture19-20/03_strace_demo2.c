#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int my_pid;
	my_pid = fork();
	// Child process
	if (my_pid == 0)
	{
		sleep(5);
	}
	else if (my_pid > 0)
	{
		// sleep(5);
		wait(NULL);
	}	
	return 0;
}

