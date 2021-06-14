#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>

#define PORTNUM 13000
#define HOSTLEN 256

int main(int argc, char **argv)
{
	struct sockaddr_in saddr;
	struct hostent *hp;

	// Address
	char hostname[HOSTLEN];
	
	int sock_id, sock_fd;
	FILE * sock_fp;

	char * ctime();
	time_t the_time;

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

	fprintf(stderr, "Setting up on host %s\n", hostname);

	// Get information about host
	hp = gethostbyname(hostname);

	// Copying across the address into our saddr struct
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

		// We be writing
		sock_fp = fdopen(sock_fd, "w");

		if (sock_fp == NULL)
		{
			perror("fdopen Error\n");
			return 1;
		}

		the_time = time(NULL);

		fprintf(sock_fp, "The time here is ..");
		fprintf(sock_fp, "%s", ctime(&the_time));
		fclose(sock_fp);
	}

	return 0;
}

