#!/bin/bash
echo "test1: $BASH_SUBSHELL"

a=$(echo "test2: $BASH_SUBSHELL")
echo $a

echo "-------------------"
echo "My PPID: $PPID"

a=$(b=$PPID; echo "My PPID: $b")
echo $a

echo "-------------------"
echo "Crazy Experiments in subsubshells"
echo $BASH_SUBSHELL
a=$(echo "test2: $BASH_SUBSHELL, $(echo "Down the rabbit hole $BASH_SUBSHELL")")
echo $a

echo "-------------------"
test_var=1;
echo "Outside the subshell: $test_var"	
let "test_var = test_var + 1" ## This is now test_var = 2
a=$(let "test_var = test_var + 1"; echo "$test_var")
echo "Inside the subshell: $a"
echo "Outside the subshell: $test_var"	
