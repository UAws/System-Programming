#!/bin/bash
echo "## Pre Paste"
echo "## File 1"
cat Files/paste1.txt
echo "## File 2:"
cat Files/paste2.txt
echo "## Combined"
paste -d " " Files/paste1.txt Files/paste2.txt
