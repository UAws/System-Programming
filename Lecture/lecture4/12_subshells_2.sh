#!/bin/bash
echo "test1: $BASH_SUBSHELL"

a=$(echo "test2: $BASH_SUBSHELL";b=$(echo "test3: $BASH_SUBSHELL");echo $b)
echo $a



