#!/bin/bash
echo "Simple use of functions"
ls | wc
echo "Piping with parameters"
ls -a | wc -l

# Why difference? Well '.' and '..' are a thing
