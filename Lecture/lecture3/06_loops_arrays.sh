#!/bin/bash
# Test for parameters
choices=( R P S L V )

# So that seems very... symboly...
for p1 in "${choices[@]}"
do
	echo $p1 $p1
done

# The crazy for loop syntax
for p1 in `seq 5 10`
do
	echo $p1
done
