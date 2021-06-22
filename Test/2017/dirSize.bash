#!/bin/bash

if (($# != 1))
then
echo 'Please input one parameter'
else
   path=$1
fi

if [[ -f $path ]]
then
    stat -c %s $path
fi

if [[ -d $path ]]
then
size=$(stat -c %s $path)
for entry in "$path"/*
do
if [[ -f $entry ]]
then
filesize=$(stat -c %s $entry)
else
filesize=$(dirSize.bash $entry)
fi
size=$(($size+$filesize))
done
echo $size
fi
