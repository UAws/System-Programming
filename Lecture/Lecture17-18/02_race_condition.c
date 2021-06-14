#include <stdio.h> 
#include <signal.h> 
#include <unistd.h>

void handle_sigquit()
{
	write(STDOUT_FILENO, "La la Start\n", 12);
	sleep(2);
	write(STDOUT_FILENO, "La la End\n", 10);
}


void handle_sigint()
{
	write(STDOUT_FILENO, "Na Na Start\n", 12);
	sleep(2);
	write(STDOUT_FILENO, "Na Na End\n", 10);
}

int main() 
{ 
 	signal(SIGINT, handle_sigint); 
	signal(SIGQUIT, handle_sigquit); 
	while (1) 
	{ 
		printf("Hello World\n"); 
		sleep(1); 
	} 
	return 0; 
} 
