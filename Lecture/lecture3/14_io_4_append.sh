#!/bin/bash
echo "Overwriting the file"
rm test_output.txt
ls | wc > test_output.txt
ls | wc > test_output.txt
cat test_output.txt

echo "Appending the file"
rm test_output.txt
ls | wc >> test_output.txt
ls | wc >> test_output.txt
cat test_output.txt
