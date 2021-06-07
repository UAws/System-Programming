#include <stdio.h>
#include <fcntl.h>  // For open
#include <unistd.h> // For close
#include <stdlib.h> // For exit

int main()
{
	int fd;
	int new_fd;
	char line[100];
	
	// Read and Print Three Lines	
	fgets(line, 100, stdin);
	printf("%s", line);
	fgets(line, 100, stdin);
	printf("%s", line);
	fgets(line, 100, stdin);
	printf("%s", line);

	fd = open("my_file.txt", O_RDONLY);

	//        On success, these system calls return the new file descriptor
	new_fd = dup2(fd, 0);
	printf("%d\n",new_fd);

	if (new_fd != 0)
	{
		fprintf(stderr, "Could not duplicate fd to 0\n");
		exit(1);	
	}


	close(fd);

	// Read and Print Three Lines	
	fgets(line, 100, stdin); // fgets is pointing at the file
	printf("%s", line);
	fgets(line, 100, stdin);
	printf("%s", line);
	fgets(line, 100, stdin);
	printf("%s", line);

	return 0;
}
