#!/bin/bash

if [ "${#}" -ne 1 ]; then
    echo "ERROR"
    exit 1
fi

if [ "${1}" -ge 1 ] && [ "${1}" -le 7 ]; then
      echo "" &> /dev/null
else
      echo "ERROR"
      exit 1
fi

case "${1}" in
  1)
    echo "red";;
  2)
    echo "orange";;
  3)
    echo "yellow";;
  4)
    echo "green";;
  5)
    echo "blue";;
  6)
    echo "indigo";;
  7)
    echo "violet";;
esac