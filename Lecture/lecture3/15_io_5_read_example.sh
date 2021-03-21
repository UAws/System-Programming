#!/bin/bash
# We haven't covered read but it basically just takes things
# and puts them in variables
echo "What is in the file?"
cat read_input.txt

echo "What does read do?"
echo "Execute this: read a b c < read_input.txt"
read a b c < read_input.txt
echo "a= "$a
echo "b= "$b
echo "c= "$c
