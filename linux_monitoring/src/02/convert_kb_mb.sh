#!/bin/bash

arg=$1
len=${#arg}

if [ $len -gt 3 ]
then
    dot=${arg:0:$len-3}'.'${arg:$len-3:2}
elif [ $len -gt 2 ]
then
    dot="0.${arg:0:$len-1}"
elif [ $len -gt 1 ]
then
    dot="0.0${arg:0:$len-1}"
else
    dot="0.00"
fi

echo $dot'MB'