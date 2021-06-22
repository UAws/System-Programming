#!/bin/bash

if [ "${#}" -ne 1 ]; then
    echo "ERROR"
    exit 1
fi

file_name=${1}


    while input_content= read -r line;
    do

#      move by shifting changed --> ${alphabet:${i}:26}
#        echo "$line" | tr "[a-z]" "[A-Z]" | tr "${alphabet:0:26}" "${alphabet:${i}:26}"
      echo "${line:0:1}";
    done < "$file_name"