all: part1 part2

part1: part1.c slow_functions.c
	gcc -std=c99 -o PART1 part1.c slow_functions.c -lpthread

part2: part2.c slow_functions.c
	gcc -std=c99 -o PART2 part2.c slow_functions.c -lpthread


clean:
	rm PART1 PART2
