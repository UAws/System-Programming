#include <stdio.h>
#include <unistd.h>

int main()
{
	char line1[100];
	char line2[100];
	printf("Type some text: \n");
	fgets(line1, 100, stdin);
	printf("Repeat: %s", line1);

	printf("Close Standard Out: \n");
	// Oh dear
	close(1);
	printf("Type some text: \n");
	fgets(line2, 100, stdin);
	printf("Repeat: %s", line2);
	return 0;
}
