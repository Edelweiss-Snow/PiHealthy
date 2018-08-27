#!/bin/bash 
echo "BadCpuLog"
Nowdate=`date +"%Y-%m-%d__%H:%M:%S"`
echo $Nowdate
declare -a id1
eval `ps aux | awk -v x=0 '{if($3 > 50 || $4 >= 50){printf("id1[%d]=%s\n", x++, $2)}}'`

if [[ ${#id1[*]} == 0 ]] 
then
    echo "Not Found bad course!!!"
    exit
fi

sleep 5
y=0
printf "signle : %-8s\t%-5s\t%-2s\t%-2s\t%-5s\n" USER PID CPU 内存 进程名
while [[ ${id1[$y]} ]] 
do
    temp=`ps aux -q ${id1[$y]} | grep ${id1[$y]}`
    PID=`echo $temp | awk '{print $2}'`
    USER=`echo $temp | awk '{print $1}'`
    CPU=`echo $temp | awk '{print $3}'`
    MEM=`echo $temp | awk '{print $4}'`
    Name=`echo $temp | awk '{print $11}'`
    if [[ $PID ]]
    then
        printf "signal 3 %-8s\t%-5s\t%-4s\t%-4s\t%-5s\n" $USER $PID $CPU $MEM $Name
    fi
    y=$[$y+1]
done
