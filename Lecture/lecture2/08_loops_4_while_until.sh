#!/bin/bash
# Test for parameters
COUNT=0

# Stay a while and listen...
while (( $COUNT < 10 ))
do
	let COUNT=COUNT+1
	echo "While: $COUNT"
done

# Like While but... NOT
until [ $COUNT -lt 1 ]
do
	let COUNT=COUNT-1
	echo "Until: $COUNT"
done

echo 
