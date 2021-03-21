#!/bin/bash
cd Files

echo "All text files"
ls *.txt

echo "All one character files"

ls ?.txt

echo "Letter Range"
ls [b-q].txt

echo "Specific letters"
ls [aqt].txt

echo "Some digits"
ls [0-9].txt

echo "Alpha"
ls [[:alpha:]][[:alpha:]].txt

echo "Digits"
ls [[:digit:]].txt

echo "Not d"
ls [!a!b].txt

cd ..
