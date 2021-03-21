#!/bin/bash
# Test for parameters
if [ $# -gt 0 ]
then
	echo "Lots of parameters"
	# Test if the first parameter is one
	if [ $1 -eq 1 ]
	then
		echo "The first parameter is 1"
	else
		echo "The first parameter is not 1"
	fi
else
	echo "No parameters :("
fi


