#!/bin/bash

choices=( R P S L V )
for p1 in "${choices[@]}"
do
	for p2 in "${choices[@]}"
	do
		./10_RPSLS.sh $p1 $p2
	done

done
