#!/bin/bash

number_re='^[0-9]+([.][0-9]+)?$'

if [[ $# = 0 ]]
then
    bash error_no_args.sh
elif [[ $# != 1 ]]
then
    bash error_many_args.sh
elif [[ $1 =~ $number_re ]]
then
    bash error_number.sh
else
    bash print.sh $1
fi