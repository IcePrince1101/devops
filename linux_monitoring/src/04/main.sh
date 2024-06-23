#!/bin/bash

colors_file="colors.conf"

name_background=6
name_font=1
value_background=6
value_font=1

name_background_is_default="True"
name_font_is_default="True"
value_background_is_default="True"
value_font_is_default="True"

chmod 777 colors.sh
function color_info()
{
    if [[ $3 == "True" ]]
    then
        arg="default ($(get_color_name $2))"
    else
        arg="$2 ($(get_color_name $2))"
    fi
    bash colors.sh $name_background $name_font $value_background $value_font $1 $arg
}

function get_color_name() 
{
    if [[ $1 == 1 ]]
    then
        echo "white"
    elif [[ $1 == 2 ]]
    then
        echo "red"
    elif [[ $1 == 3 ]]
    then
        echo "green"
    elif [[ $1 == 4 ]] 
    then
        echo "blue"
    elif [[ $1 == 5 ]]
    then
        echo "purple"
    elif [[ $1 == 6 ]]
    then
        echo "black"
    fi
}

colors=`awk '{a = a " " $1} END {print a}' $colors_file`
list_colors=($colors)
length=${#list_colors[@]}

for ((i=0; i<length; i++))
do
    if [[ ${list_colors[i]} =~ "column1_background=" ]]
    then
        name_background=${list_colors[i]: -1}
        name_background_is_default="False"
    elif [[ ${list_colors[i]} =~ "column1_font_color=" ]]
    then
        name_font=${list_colors[i]: -1}
        name_font_is_default="False"
    elif [[ ${list_colors[i]} =~ "column2_background=" ]]
    then
        value_background=${list_colors[i]: -1}
        value_background_is_default="False"
    elif [[ ${list_colors[i]} =~ "column2_font_color=" ]]
    then
        value_font=${list_colors[i]: -1}
        value_font_is_default="False"
    fi
done

if [[ $# != 0 ]]
then
    echo "Args must be empty"
    exit 1
elif [[ $name_background != [1-6] || $name_font != [1-6] || $value_background != [1-6] || $value_font != [1-6] ]]
then
    echo "Args must be from 1 to 6"
    exit 1
elif [[ $name_background == $name_font || $value_background == $value_font ]]
then
    echo "Color of text and background must be different"
    exit 1
fi

chmod 777 get_info.sh
info=$(bash get_info.sh $name_background $name_font $value_background $value_font)

echo -e "$info\n"

color_info "column1_background" $name_background $name_background_is_default
color_info "column1_font_color" $name_font $name_font_is_default
color_info "column2_background" $value_background $value_background_is_default
color_info "column2_font_color" $value_font $value_font_is_default

exit 0