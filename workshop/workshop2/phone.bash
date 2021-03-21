#!/bin/bash

file_name='input.txt'

    while input_content= read -r line;
    do

#      move by shifting changed --> ${alphabet:${i}:26}
        echo "$line" | grep "$1"

    done < "$file_name"