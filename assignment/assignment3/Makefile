all: part1 part2 part3

part1: smsh2.c splitline.c execute2.c
	gcc -std=c99 -o smsh2 smsh1.c splitline.c execute2.c

part2: smsh3.c splitline.c execute3.c
	gcc -std=c99 -o smsh3 smsh2.c splitline.c execute3.c

part3: smsh3.c splitline.c execute3.c
	gcc -std=c99 -o smsh4 smsh3.c splitline.c execute4.c

clean:
	rm smsh2 smsh3 smsh4
