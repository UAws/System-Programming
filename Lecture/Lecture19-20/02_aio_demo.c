#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <aio.h>

int notdone=1;
struct aiocb my_buffer;

void on_input(int);
void setup_aio_buffer();

int main(int argc, char **argv)
{
	system("stty raw -echo");

	setup_aio_buffer();
	aio_read(&my_buffer);
	signal(SIGIO, on_input);
	
	while (notdone)
	{
	}
	return 0;
}

void on_input(int signum)
{
    char *cp = (char *) my_buffer.aio_buf;

	// Chec for errors

	if ( aio_error(&my_buffer) != 0 )
	{
		perror("reading failed - timing?");
	}
	else 
	{
		// Get number of chars read
		if ( aio_return(&my_buffer) == 1 )
		{
			if ( *cp == 'Q' || *cp == EOF )
			{
				system("stty cooked echo"); /* should do this without shelling out to stty */
				exit(0);
			}
			// The example functionality
			else if ( *cp == 'n' )
			{
				printf("Quack\n\r");
			}
		}
	}
	// place a new request
	aio_read(&my_buffer);
}


void setup_aio_buffer()
{
	static char input[1];		      /* 1 char of input */

	/* describe what to read */
	my_buffer.aio_fildes     = 0;	      		/* standard intput */
	my_buffer.aio_buf        = input;	      /* buffer          */
	my_buffer.aio_nbytes     = 1;             /* number to read  */
	my_buffer.aio_offset     = 0;             /* offset in file  */

	/* describe what to do when read is ready */
	my_buffer.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	my_buffer.aio_sigevent.sigev_signo  = SIGIO;  /* send sIGIO   */
}
