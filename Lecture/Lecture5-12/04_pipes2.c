#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
	char input_str[100];
	char input_str2[100];
	int pipe1[2];
	pid_t my_pid;

	// Boring Pipe Failure Stuff
	if (pipe(pipe1) == -1)
	{
		printf("Error, Pipe 1 Failed\n");
		return 1;
	}

	printf("Type something\n");
	scanf("%s", input_str);

	my_pid = fork();

	// Fork Fail
	if (my_pid < 0)
	{
		printf("Failed Fork\n");	
	}
	
	// Fork Parent
	else if (my_pid > 0)
	{
		
		close(pipe1[0]); // close pipe reading end 
		dup2(pipe1[1], 1); // reopen stdout , copy write end to stdout 
		close(pipe1[1]);  // close write end
		printf("%s\n", input_str); // cout 
		wait(NULL);
	}
	
	// Fork Child
	else
	{
		close(pipe1[1]); // close writing end
		dup2(pipe1[0], 0); // reopen stdin, copy reading to stdin 

		close(pipe1[0]); // close reading end 
		scanf("%s", input_str2);
	
		printf("C: From pipe: %s\n", input_str2);
	}

}




