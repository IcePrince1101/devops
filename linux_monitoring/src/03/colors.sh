#!/bin/bash

white_font="\e[1;37m"
red_font="\e[1;31m"
green_font="\e[1;32m"
blue_font="\e[1;34m"
purple_font="\e[1;35m"
black_font="\e[1;30m"

white_background="\e[1;47m"
red_background="\e[1;41m"
green_background="\e[1;42m"
blue_background="\e[1;44m"
purple_background="\e[1;45m"
black_background="\e[1;40m"

name_background=$1
name_font=$2
value_background=$3
value_font=$4
name=$5
value="$*"

function set_color() 
{
    background=$(set_background $1)
    font=$(set_font $2)
    echo "${background}${font}"
}

function reset_color() 
{
    echo "${black_background}${white_font}"
}

function set_background() 
{
    if [[ $1 == 1 ]]
    then
        echo $white_background
    elif [[ $1 == 2 ]]
    then
        echo $red_background
    elif [[ $1 == 3 ]]
    then
        echo $green_background
    elif [[ $1 == 4 ]]
    then
        echo $blue_background
    elif [[ $1 == 5 ]]
    then
        echo $purple_background
    elif [[ $1 == 6 ]]
    then
        echo $black_background
    fi
}

function set_font() 
{
    if [[ $1 == 1 ]]
    then
        echo $white_font
    elif [[ $1 == 2 ]]
    then
        echo $red_font
    elif [[ $1 == 3 ]]
    then
        echo $green_font
    elif [[ $1 == 4 ]]
    then
        echo $blue_font
    elif [[ $1 == 5 ]]
    then
        echo $purple_font
    elif [[ $1 == 6 ]]
    then
        echo $black_font
    fi
}

echo -e "$(set_color $name_background $name_font)$name$(reset_color) = $(set_color $value_background $value_font)$value$(reset_color)"