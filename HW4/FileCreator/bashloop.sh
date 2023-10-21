#!/bin/bash

if  [ $# -ne 2 ]; then
	echo "Error"
	exit 1
fi

N=$1
Text=$2

for ((i=1; i<=N; ++i)); do
	echo "$Text $i" > "file_$i.txt"
done

