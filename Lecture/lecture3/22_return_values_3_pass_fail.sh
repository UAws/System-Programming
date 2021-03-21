#!/bin/bash
gcc Pass.c -o Pass
gcc Fail.c -o Fail
echo "## Fail Alone"
if $(./Fail); then
	echo "Fail worked"
else
	echo "Fail didn't work"
fi

echo "## Pass Alone"
if $(./Pass); then
	echo "Pass worked"
else
	echo "Pass didn't work"
fi

echo "## Fail && Pass"
if $(./Fail) && $(./Pass); then
	echo "Fail & Pass worked"
else
	echo "Fail & Pass didn't work"
fi

echo "## Pass && Fail"
if $(./Pass) && $(./Fail); then
	echo "Pass & Fail worked"
else
	echo "Pass & Fail didn't work"
fi

echo "## Pass || Fail"
if $(./Pass) || $(./Fail); then
	echo "Pass OR Fail worked"
else
	echo "Pass OR didn't work"
fi
