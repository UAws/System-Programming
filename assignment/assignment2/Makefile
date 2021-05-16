all: sequence pipeline

sequence: sequence.c common.c
	gcc -std=c99 sequence.c common.c -o sequence

pipeline: pipeline.c common.c
	gcc -std=c99 pipeline.c common.c -o pipeline

clean:
	rm sequence pipeline
