#include <stdio.h> 
#include <signal.h> 
#include <unistd.h>

char input[100];

void handle_sigint()
{
	printf("Na na\n");
}

int main() 
{ 
    signal(SIGINT, handle_sigint); 
    while (1) 
    { 
        printf("Type something\n"); 
		fgets(input, 100, stdin);
		printf("Return: %s\n", input);
    } 
    return 0; 
} 
