#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd;
	char line[100];
	
	// Read and Print Three Lines	
	fgets(line, 100, stdin);
	printf("%s", line);
	fgets(line, 100, stdin);
	printf("%s", line);
	fgets(line, 100, stdin);
	printf("%s", line);

	close(0); // Close stdin
	fd = open("my_file.txt", O_RDONLY);
	if (fd != 0)
	{
		fprintf(stderr, "Could not open data as fd 0\n");
		exit(1);	
	}

	// Read and Print Three Lines	
	fgets(line, 100, stdin);
	printf("%s", line);
	fgets(line, 100, stdin);
	printf("%s", line);
	fgets(line, 100, stdin);
	printf("%s", line);

	return 0;
}
