#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>
#include <ctype.h>

#define PORTNUM 11000
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

// Fork stuff
int process_request(int in_fd, char * in_dirname)
{
	int dirlen, c;

	FILE * sock_fpo;

	int pid = fork();
	if (pid == -1)
	{
		printf("Error with forking\n");
		return 1;
	}
	// CHILD
	else if (pid == 0)
	{
		printf("Child\n");

		// We be reading too
		

		printf("Received dirname: %s\n", in_dirname);
		dup2(in_fd, 1);
		printf("Begin Wait\n");
		sleep(5);
		printf("End Wait\n");
		execlp("ls", "ls", in_dirname, (char *)NULL);
		exit(1);
	}
	// PARENT
	else if (pid > 0)
	{
		printf("Parent\n");
		//execlp("ls", "ls", (char *)NULL);
		//wait(NULL);
		
		return 0;
	}
}

int main(int argc, char **argv)
{
	struct sockaddr_in saddr;
	struct hostent * hp;


	// Address
	char hostname[HOSTLEN];
	int sock_id, sock_fd;
	FILE * sock_fpi;		// Stream for in

	char dirname[BUFSIZ];
	char command[BUFSIZ];

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

	fprintf(stderr, "Setting up on host %s, %d\n", hostname, atoi(argv[1]));

	// Get information about host
	hp = gethostbyname(hostname);

	bcopy((void *)hp->h_addr, (void *)&saddr.sin_addr, hp->h_length);
	
	// Fill in socket port number
	saddr.sin_port = htons(atoi(argv[1]));

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

		if (sock_fd == -1)
		{
			perror("Accept Error\n");
			return 1;
		}
		else
		{
			printf("Received a call!\n");
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
		process_request(sock_fd, dirname);
		sleep(1);
		fclose(sock_fpi);
		close(sock_fd);
	}

	return 0;
}

