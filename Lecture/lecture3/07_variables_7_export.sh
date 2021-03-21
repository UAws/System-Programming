#!/bin/bash
echo "## What is in export_script.sh?"
cat 07_export_script.sh

a=5

echo "## Run without export"
./07_export_script.sh
echo "## Run with export"
export a
./07_export_script.sh
