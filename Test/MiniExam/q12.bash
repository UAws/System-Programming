#!/bin/bash

SUM=0;

#echo $#

if [[ $# -lt 2 ]]; then
    echo "Error"
else
   for i in "${@}" ; do
     SUM=$(( ${SUM} + ${i} ))
   done

   echo "${SUM}"
fi