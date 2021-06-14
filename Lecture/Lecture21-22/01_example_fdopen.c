#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int fd;
	FILE * my_file;
	fd = open("test1.txt", O_RDWR);

	my_file = fdopen(fd, "w");
	fprintf(my_file, "Hello darkness my old friend\n");
	fclose(my_file);	

	return 0;
}

