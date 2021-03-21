#!/bin/bash
echo "Here we assign 'a' and then we print it out"
a=1
echo "a=$a"

echo "Here we assign 'b' to the output of ls..."
b=$(ls)
echo $b

c="words with spaces"
c=words with spaces
