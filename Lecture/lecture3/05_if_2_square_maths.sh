#!/bin/bash
echo "Here we go!"
if [ $# -ge 1 ]
then
	if [ $1 -eq 1 ]
	then
		echo "$1 equals 1"
	else	
		echo "$1 does not equal 1"
	fi

	if (($1 + $# > 3))
	then
		echo "Hooray"
	else	
		echo "Boo"
	fi
else
	echo "Bad parameters"
fi
