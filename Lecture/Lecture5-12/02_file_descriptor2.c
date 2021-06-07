#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char line1[100];
	char line2[100];
	printf("Type some text: \n");
	fgets(line1, 100, stdin);
	printf("Repeat: %s", line1);

	printf("Close Standard In: \n");
	// Oh dear
	close(0);

	printf("Maybe read from a file instead?\n");
	int fd;
	fd = open("input.txt", O_RDONLY);

	fgets(line2, 100, stdin);
	printf("%s", line2);
	fgets(line2, 100, stdin);
	printf("%s", line2);
	return 0;
}
