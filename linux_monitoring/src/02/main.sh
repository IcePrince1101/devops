#!/bin/bash

if [[ $# != 0 ]]
then
    echo "Too many args!"
    exit 1
fi

info=$(bash get_info.sh)

echo "$info"

echo "Read this data to the file? (Y/N)"
read answer

if [[ $answer == 'Y' || $answer == 'y' ]]
then
    filename=$(date +'%d_%m_%y_%H_%M_%S')'.status'
    echo "$info" > $filename
    echo "File $filename created"
fi
exit 0