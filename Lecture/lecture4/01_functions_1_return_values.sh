#!/bin/bash
function f_return1 ()
{
	echo 5
	return 1
}

function f_return2 ()
{
	echo "A duck goes $1"
	echo "$2"
	return 5;
}

# So returns are actually the stdout output not the return value
echo "##################"
echo "Doomed to failure"
a=$(f_return1)
echo "Shouldn't there be something: $a : "

# 
echo "##################"
echo "Doomed to echo"
a=$(f_return2 quack)
echo $a

echo "##################"
echo "Doomed to echo"
a=$(f_return2 quack huzzahs ladida)
echo $a


#f_return2 hi quack

echo "##################"
echo "What is going on here..."
a=$(f_return1)
echo $?
echo $?
