#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define PORTNUM 13000
#define HOSTLEN 256

int main(int argc, char **argv)
{
	struct sockaddr_in servadd;
	struct hostent     * hp;
	int    sock_id, sock_fd;
	char   buffer[BUFSIZ];
	int    n_read;

	if (argc != 4)
	{
		perror("Wrong number of arguments\n");
		return 1;
	}

	// ##################################################
	// ## PART 1: Get a socket

	sock_id = socket( AF_INET, SOCK_STREAM, 0);
	if (sock_id == -1)
	{
		perror("Client Socket Error");
		return 1;
	}
	
	// ##################################################
	// ## PART 2: Connect to server

	// Zero the address
	bzero(&servadd, sizeof(servadd));

	hp = gethostbyname(argv[1]);
	if (hp == NULL)
	{
		perror(argv[1]);
		return 1;
	}

	bcopy(hp->h_addr, (struct sockaddr *) &servadd.sin_addr, hp->h_length);

	servadd.sin_port = htons(atoi(argv[2]));
	servadd.sin_family = AF_INET;

	// Dial
	if (connect(sock_id, (struct sockaddr *) &servadd, sizeof(servadd)) != 0)
	{
		perror("Client Connect Error\n");
		return 1;
	}

	// ##################################################
	// ## PART 3: The substance

	// printf("Part 3: 'ls %s'\n", argv[3]);
	if (write(sock_id, argv[3], strlen(argv[3])) == -1)
	{
		perror("Write Error\n");
		return 1;
	}
	if (write(sock_id, "\n", 1) == -1)
	{
		perror("Write Error\n");
		return 1;
	}
	
	printf("Before read: %s\n", buffer);


	while (1)
	{
		n_read = read(sock_id, buffer, BUFSIZ);
		if (n_read <= 0)
		{
			printf("Nothing left to read\n");
			break;
		}
		else
		{
			//printf("%s\n", buffer);
		}

		if (write(1, buffer, n_read) == -1)
		{
			perror("Write Error\n");
			return 1;	
		}



	}
	printf("After Read: \n%s\n", buffer);
	close(sock_id);

	return 0;	
}

