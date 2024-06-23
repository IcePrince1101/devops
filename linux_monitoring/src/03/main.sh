#!/bin/bash

if [[ $# != 4 ]]
then
    echo "Need 4 args"
    exit 1
elif [[ $1 != [1-6] || $2 != [1-6] || $3 != [1-6] || $4 != [1-6] ]]
then
    echo "Args must be from 1 to 6"
    exit 1
elif [[ $1 == $2 || $3 == $4 ]]
then
    echo "Color of text and background must be different"
    exit 1
fi

info=$(bash get_info.sh $1 $2 $3 $4)

echo "$info"

exit 0