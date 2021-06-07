#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int id, fd;

	printf("About to run who into a file\n");
	id = fork();
	printf("Fork: %d\n", id);
	// Child
	if (id == 0)
	{

		printf("I am a child\n");
		
		close(1); // Close Stdout
		fd = creat("userlist", 0644); // Then Open
		execlp("who", "who", NULL);
		perror("execlp");			// We shouldn't get here
		exit(1);
		
	}
	if (id != 0)
	{
		printf("Parent\n");
		wait(NULL);
		printf("Done running who! Results in userlist\n");
	}

	return 0;
}
