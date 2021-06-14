/* sigactdemo.c
 *               purpose: shows use of sigaction()
 *               feature: blocks ^\ while handling ^C
 *                        does not reset ^C handler, so two kill
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#define	INPUTLEN	100

int main(int argc, char * argv[])
{
	int do_mousetrap = 0;
	int do_exit = 0;

	if (argc > 1)
	{
		if (strcmp(argv[1], "mouse") == 0)
		{
			printf("Mouse Trap\n");
			do_mousetrap = 1;
		}
	}

	struct 		sigaction new_action;  // Settings Struct
	sigset_t    blocked;               // To be used later for block mask
	void		sigint_handler();      // Our handler
	char		x[INPUTLEN];
    
	new_action.sa_handler = sigint_handler;			// Set the handler function

	// Set Flags
	// RESET HAND makes it like a mousetrap (can only happen once)
	// RESTART    makes it resume rather than crashing out with an error
	if (do_mousetrap == 1)
	{
		new_action.sa_flags   = SA_RESETHAND | SA_RESTART;	
	}
	else
	{    
		new_action.sa_flags   = SA_RESTART;
	}
	// This is some inbuilt functions which are basically building a list for a mask
	sigemptyset(&blocked);			// Initialise list
	sigaddset(&blocked, SIGQUIT);	// Add SIGQUIT
	new_action.sa_mask = blocked;	// Set the mask
    
	// Assign the sigaction (assuming it doesn't screw up go to else)
	if ( sigaction(SIGINT, &new_action, NULL) == -1 )
	{
		perror("sigaction");
	}
	else
	{
		while( 1 )
		{
			fgets(x, INPUTLEN, stdin);
			printf("input: %s", x);
		}
	}
}

void sigint_handler(int s)
{
    printf("\nCalled with signal %d\n", s);
    sleep(5);
    printf("Done handling signal %d\n", s);
}
