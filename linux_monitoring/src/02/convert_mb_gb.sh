#!/bin/bash

arg=$1
len=${#arg}

if [ $len -gt 3 ]
then
    dot=${arg:0:$len-3}'.'${arg:$len-3:3}
elif [ $len -gt 2 ]
then
    dot="0.${arg}"
elif [ $len -gt 1 ]
then
    dot="0.0${arg}"
elif [ $len -gt 0 ]
then
    dot="0.00${arg}"
else
    dot="0.000"
fi

echo $dot'GB'