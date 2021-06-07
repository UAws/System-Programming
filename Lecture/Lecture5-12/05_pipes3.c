#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
	char * commands1[2];
	commands1[0] = "ls";
	commands1[1] = NULL;
	
	char * commands2[2];
	commands2[0] = "wc";
	commands2[1] = NULL;

	char test_buffer[100];

	int my_pipe[2];
	pid_t my_pid;

	// Boring Pipe Failure Stuff
	if (pipe(my_pipe) == -1)
	{
		printf("Error, Pipe Failed\n");
		return 1;
	}

	printf("Let's Go!\n");
	printf("123\n");


	//scanf("%s", input_str);

	my_pid = fork();

	// Fork Fail
	if (my_pid < 0)
	{
		printf("Failed Fork\n");	
	}
	
	// Fork Parent
	else if (my_pid > 0)
	{
		
		printf("parent\n");
		close(my_pipe[1]);
		dup2(my_pipe[0], 0);
		close(my_pipe[0]);
		wait(NULL);
		execvp(commands2[0], commands2);
	}
	
	// Fork Child
	else
	{
		printf("child\n");
		close(my_pipe[0]);
		dup2(my_pipe[1], 1);
		close(my_pipe[1]);
		execvp(commands1[0], commands1);
	}


}




