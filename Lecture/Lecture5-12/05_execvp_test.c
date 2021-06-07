#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	char * commands[2];
	
	commands[0] = "ls";
	commands[1] = NULL;

	char * commands2[2];
	commands2[0] = "wc";
	commands2[1] = NULL;	

	char test_buffer[100];

	pid_t my_pid;

	int my_pipe[2];

	// Create a pipe
	if (pipe(my_pipe) == -1) {
		perror("Cannot create pipe");
	}


	my_pid = fork();

	// Fork Fail
	if (my_pid < 0)
	{
		printf("Failed Fork\n");	
	}
	
	// Parent: The Reader
	if (my_pid > 0)
	{
		// Close Write
		close(my_pipe[1]);
		
		dup2(my_pipe[0], STDIN_FILENO);
		// wait (NULL);

		
		execvp("wc", commands2);
		//scanf("%s", test_buffer);
		//printf("Parent: %s\n", test_buffer);
		//read(my_pipe[0], test_buffer, 100);
		//printf("Read: %s\n", test_buffer);
	}

	// Child: The Writer
	else
	{	
		// Close Read
		close(my_pipe[0]);	

		dup2(my_pipe[1], STDOUT_FILENO);
		//printf("Hello\n");
		//write(my_pipe[1], "hello", strlen("hello") + 1);


		execvp("ls", commands);
	}
	//
}
