#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// Predefine some functions
void on_input(int);
void enable_kbd_signals();

int notdone=1;
int main(int argc, char **argv)
{
	system("stty raw -echo"); // What is this?
	signal(SIGIO, on_input);  // SIGIO 
	enable_kbd_signals();     // What is this?

	while (notdone)
	{
	}
	return 0;
}

// The meaningful functionality
void on_input(int signum)
{
	int c = getc(stdin);

	// The escape clause
	if ( c == 'Q' || c == EOF )
	{
		system("stty cooked echo"); // What is this?
		exit(0);
	}

	// The example functionality
	else if ( c == 'n' )
	{
		printf("Quack\n\r");
	}
}

// Sets up the appropriate flags for the keyboard signals
void enable_kbd_signals()
{
	int  fd_flags;

	fcntl(0, F_SETOWN, getpid());
	fd_flags = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, (fd_flags|O_ASYNC));
}

