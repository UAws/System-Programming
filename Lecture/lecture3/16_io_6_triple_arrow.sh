#!/bin/bash

read lines words chars filename <<< $(wc test_input.txt)
echo $lines
echo $words
echo $chars
echo $filename
