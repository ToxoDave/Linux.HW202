#!bin/bash

mkdir workDir
touch ./workDir/message.txt
echo $@ > ./workDir/message.txt

