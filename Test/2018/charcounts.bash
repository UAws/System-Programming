#!/bin/bash

  if [ "${#}" -ne 1 ]; then
    echo "ERROR"
    exit 1
  fi

charcounts(){

  file_name=${1}

  while input_content= read -r line;
    do

#      move by shifting changed --> ${alphabet:${i}:26}
      tmp=$(echo "${line}" | grep "zzz")

      if [ $? -eq 0 ]; then
          echo "${tmp}" | wc -c | sed 's/ //g';
      fi

  done < "$file_name"

}


charcounts "${1}"