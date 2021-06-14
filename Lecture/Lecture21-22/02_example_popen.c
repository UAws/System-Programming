#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	const int PATH_MAX = 100;
	char my_string[PATH_MAX];

	FILE * my_file;

	my_file = popen("ls", "r");
	while (fgets(my_string, PATH_MAX, my_file) != NULL)
	{
		printf("I read this: %s", my_string);
	}	
	pclose(my_file);	
	printf("####################\n");
	printf("## We're All Done ##\n");
	return 0;
}

