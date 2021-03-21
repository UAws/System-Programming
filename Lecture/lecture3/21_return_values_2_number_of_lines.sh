#!/bin/bash
# Description:
# - Applies a word count to the first parameter 
#   and return the number of lines (stored in nrLines)
# What is the point:
# - If you don't supply a file, it will return '1'
# - If you do, it works
nrLines=$(wc -l < "$1")
echo "$?"
echo "$nrLines in $1"
