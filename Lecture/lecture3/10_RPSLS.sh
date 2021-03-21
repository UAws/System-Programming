#!/bin/bash
choices=( R L V S P )
i1=0
i2=0

#read -r a
#read -r b

echo $a

for p1 in "${choices[@]}"
do
	if [ "$p1" == "$1" ]
	then
		break
	else
		#echo $i1
		let i1=i1+1
	fi
done

for p1 in "${choices[@]}"
do
	if [ "$p1" == "$2" ]
	then
		break
	else
		#echo $i2
		let i2=i2+1
	fi
done

winner=0
if (( i1 > i2 ))
#if [ $i1 -gt $i2 ]
then
	if [[ $(( (i1 - i2) % 2 )) == 0 ]]
	then	
		let winner=1
	else
		let winner=2
	fi
fi

if (( i2 > i1 ))
then
	if [[ $(( (i2 -i1) % 2 )) == 0 ]]
	then	
		let winner=2
	else
		let winner=1
	fi
fi


echo $1 $2 $winner

