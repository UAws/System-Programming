all: sequence pipeline

sequence: sequence.c common.c
	gcc sequence.c common.c -o sequence

pipeline: pipeline.c common.c
	gcc pipeline.c common.c -o pipeline

clean:
	rm sequence pipeline
