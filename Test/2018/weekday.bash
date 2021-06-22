#!/bin/bash

if [ "${#}" -ne 1 ]; then
    echo "ERROR"
    exit 1
fi

if [ "${1}" -ge 1 ] && [ "${1}" -le 7 ]; then
      echo "" &> /dev/null
else
      echo "ERROR"
fi

case "${1}" in
  1)
    echo "Mon";;
  2)
    echo "Tue";;
  3)
    echo "Wed";;
  4)
    echo "Thu";;
  5)
    echo "Fri";;
  6)
    echo "Sat";;
  7)
    echo "Sun";;
esac