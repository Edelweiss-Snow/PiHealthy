#!/bin/bash
x=0
file=`ls | grep -x master`
if [[ -z $file ]]
then
    x=1
else
    x=2
fi

if [[ $x -eq 1 ]]
then
    gcc master.c -o master
    ./$file &
else
    ./$file &
fi
