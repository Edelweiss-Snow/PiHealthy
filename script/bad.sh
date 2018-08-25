#!/bin/bash 
echo "BadCpuLog" >> BadLog
Nowdate=`date -u +"%Y-%m-%d__%H:%M:%S"`
echo $Nowdate >> BadLog
declare -a id1
eval `ps aux | awk -v x=0 '{if($3 > 50 || $4 >= 50){printf("id1[%d]=%s\n", x++, $2)}}'`

if [[ ${#id1[*]} == 0 ]] 
then
    echo "Not Found bad course!!!" >> BadLog
    exit
fi

sleep 5
y=0
printf "%-8s\t%-5s\t%-2s\t%-2s\t%-5s\n" USER PID CPU 内存 进程名 >> Log
while [[ ${id1[$y]} ]] 
do
    temp=`ps aux -q ${id1[$y]} | tail -1`
    PID=`echo $temp | awk '{print $2}'`
    USER=`echo $temp | awk '{print $1}'`
    CPU=`echo $temp | awk '{print $3}'`
    MEM=`echo $temp | awk '{print $4}'`
    Name=`echo $temp | awk '{print $11}'`
    if [[ $PID ]]
    then
        printf "%-8s\t%-5s\t%-4s\t%-4s\t%-5s\n" $USER $PID $CPU $MEM $Name >> BadLog
    fi
    y=$[$y+1]
done
