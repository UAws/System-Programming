#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>
#include <ctype.h>

#define PORTNUM 12000
#define HOSTLEN 256


// Simple function for removing non-address things from code
void sanitize(char * str)
{
	char * src;
	char * dest;
	for (src = dest = str; *src; src++)
	{
		if (*src == '/' || isalnum(*src))
		{
			*dest++ = *src;
		}
	}
	*dest = '\0';
}

int main(int argc, char **argv)
{
	struct sockaddr_in saddr;
	struct hostent * hp;

	// Address
	char hostname[HOSTLEN];
	
	int sock_id, sock_fd;
	FILE * sock_fpi;		// Stream for in
	FILE * sock_fpo;		// Stream for out
	FILE * pipe_fp;

	char dirname[BUFSIZ];
	char command[BUFSIZ];

	int dirlen, c;

	// ##################################################
	// ## PART 1: Get a socket

	sock_id = socket( PF_INET, SOCK_STREAM, 0);	

	if (sock_id == -1)
	{
		perror("Socket Error\n"); 
		return 1;
	}

	// ##################################################
	// ## PART 2: Binding

	// Clear out struct
	bzero((void *) &saddr, sizeof(saddr));

	gethostname(hostname, HOSTLEN);

	fprintf(stderr, "Setting up on host %s, %d\n", hostname, PORTNUM);

	// Get information about host
	hp = gethostbyname(hostname);

	bcopy((void *)hp->h_addr, (void *)&saddr.sin_addr, hp->h_length);
	
	// Fill in socket port number
	saddr.sin_port = htons(PORTNUM);

	// Fill in ADDR family
	saddr.sin_family = AF_INET;

	if (bind(sock_id, (struct sockaddr *) &saddr, sizeof(saddr)) != 0)
	{
		perror("Bind Error\n"); 
		return 1;
	}

	// ##################################################
	// ## PART 3: Listen

	if (listen(sock_id, 1) != 0)
	{
		perror("Listen Error\n");
		return 1;
	}

	// ##################################################
	// ## PART 4: Functionality

	while (1) // True
	{
		sock_fd = accept(sock_id, NULL, NULL);
		printf("Received a call!\n");

		if (sock_fd == -1)
		{
			perror("Accept Error\n");
			return 1;
		}

		// We be reading too
		if ((sock_fpi = fdopen(sock_fd, "r")) == NULL)
		{
			perror("fdopen Reading Error\n");
			return 1;
		}
		
		// Get some stuff
		if (fgets(dirname, BUFSIZ-5, sock_fpi) == NULL)
		{
			perror("reading dirname");
			return 1;		
		}

		sanitize(dirname);

        if ((sock_fpo = fdopen(sock_fd,"w")) == NULL )
		{
			perror("fdopen Writing Error\n");
			return 1;
		}

		sprintf(command, "ls %s", dirname);

		printf("ls %s\n", dirname);

		if ((pipe_fp = popen(command, "r")) == NULL)
		{
			perror("Process Open Error\n");
			return 1;
		}

		while (1)
		{
			c = getc(pipe_fp);
			if (c == EOF)
			{
				printf("Nothing left to read\n");
				break;
			}
			putc(c, sock_fpo);
		}
		pclose(pipe_fp);
		fclose(sock_fpo);
		fclose(sock_fpi);
	}

	return 0;
}

