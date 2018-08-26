#!/bin/bash 
Nowdate=`date -u +"%Y-%m-%d__%H:%M:%S"`
NowAvg=`cat /proc/loadavg | awk '{print $1,$2,$3}'`
Cputem=$(echo "scale=2;((`cat /sys/devices/virtual/thermal/thermal_zone0/temp`)/1000)" | bc)
idle1=`cat /proc/stat | head -1 | awk '{print $5}'`
Cpu1=`cat /proc/stat | head -1 | awk '{printf("%d\n", $2+$3+$4+$5+$6+$7+$8);}'`
sleep 5
idle2=`cat /proc/stat | head -1 | awk '{print $5}'`
Cpu2=`cat /proc/stat | head -1 | awk '{printf("%d\n", $2+$3+$4+$5+$6+$7+$8);}'`
temp=$(echo "scale=4;(1-$[$idle2-$idle1]/$[$Cpu2-$Cpu1])*100" | bc)
echo "CpuLog"
echo "$Nowdate"
echo "$NowAvg $Cputem $temp"
