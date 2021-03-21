#!/bin/bash

a="Quack"
echo '$a$a'
echo $a$a
echo '${a:0:2}'
echo ${a:0:2}
echo '${a:2:2}'
echo ${a:2:2}
echo '${a#Qu}'
echo ${a#Qu}
echo '${a%ack}'
echo ${a%ack}
echo '${a/c/t}'
echo ${a/c/t}