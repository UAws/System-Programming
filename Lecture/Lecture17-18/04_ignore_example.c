#include <stdio.h> 
#include <signal.h> 
#include <unistd.h>

int main() 
{ 
    signal(SIGINT, SIG_IGN); 
    while (1) 
    { 
        printf("Hello World\n"); 
        sleep(1); 
    } 
    return 0; 
} 
