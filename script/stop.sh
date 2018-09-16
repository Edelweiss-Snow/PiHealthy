#!/bin/bash 
x=$1
temp=`ps aux | grep x | grep -v grep`

if [[ -z $temp ]]
then
    echo "已经没有运行的$x"
else
    pkill $x
    rm -rf $x
    echo "已经关闭$x"
fi

