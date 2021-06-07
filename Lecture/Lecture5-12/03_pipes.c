#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int pipe1[2];
	int pipe2[2];
	
	char fixed_str[] = " bob";
	char input_str[100];

	pid_t my_pid;

	// Boring Pipe Failure Stuff
	if (pipe(pipe1) == -1)
	{
		printf("Error, Pipe 1 Failed\n");
		return 1;
	}
	if (pipe(pipe2) == -1)
	{
		printf("Error, Pipe 2 Failed\n");
		return 1;
	}

	printf("Type something\n");
	scanf("%s", input_str);
	printf("I: %s\n", input_str);

	my_pid = fork();

	// Fork Fail
	if (my_pid < 0)
	{
		printf("Failed Fork\n");
	}
	
	// Fork Parent
	else if (my_pid > 0)
	{
		char quack[100];

		printf("P: Pipe FDs: %d, %d \n", pipe1[0], pipe1[1]);

		// Closes the reading end of pipe1
		close(pipe1[0]);
		printf("P: Close pipe1[0]\n");	

		// Write something to pipe1
		printf("P: Write pipe1\n");
		write(pipe1[1], input_str, strlen(input_str) + 1);
	
		// Closes the writing end of pipe1
		close(pipe1[1]);
		printf("P: Close pipe1[1]\n");

		// Wait for the child process
		wait(NULL);

		// Closes the writing end of pipe2
		close(pipe2[1]);
		printf("P: Close pipe2[1]\n");

		printf("P: Read pipe2\n");
		read(pipe2[0], quack, 100);

		// Closes the reading end of pipe2
		close(pipe2[0]);
		printf("P: Close pipe2[0]\n");

		printf("P: %s\n", quack);

	}
	
	// Fork Child
	else
	{
		printf("C: Pipe FDs: %d, %d \n", pipe1[0], pipe1[1]);

		// Closes the writing end of pipe1
		close(pipe1[1]);
		printf("C: Close pipe1[1]\n");

		char concat_str[100];

		printf("C: Read pipe1\n");
		read(pipe1[0], concat_str, 100);

		// Close both reading ends
		close(pipe1[0]);
		printf("C: Close pipe1[0]\n");

		printf("C: %s\n", concat_str);

		int k = strlen(concat_str);
		int i;
		for (i = 0; i < strlen(fixed_str); i++)
		{
			concat_str[k++] = fixed_str[i];
		}
		
		// String null terminator
		concat_str[k] = '\0';
		printf("C: %s\n", concat_str);

		printf("C: Pipe FDs: %d, %d \n", pipe2[0], pipe2[1]);

		close(pipe2[0]);
		printf("C: Close pipe2[0]\n");	

		printf("C: Write pipe2\n");
		write(pipe2[1], concat_str, strlen(concat_str) + 1);
		close(pipe2[1]);
		printf("C: Close pipe2[1]\n");

		exit(0);
	}

}




