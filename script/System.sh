#!/bin/bash
date=`date +"%Y-%m-%d__%H:%M:%S"`
hostname=`hostname`
uname="`cat /etc/issue | awk '{print $1$2}'`/`uname -r`"
utime="`uptime | tr "," " " | awk '{print $2"_"$3"_"$4}'` `uptime | tr "," " " | awk '{print $5}'`"
cpu=`cat /proc/loadavg | awk '{print $1,$2,$3}'`
disk=`df -m | tr -s " " | sed "1,1d" | head -1 | awk '{print $2,$5}'`
mem=`free -m | sed -n '2p' | awk '{printf("total:%d,used:%.4f%%",$2,$3/$2*100)}'`
Cputem=$(echo "scale=2;((`cat /sys/devices/virtual/thermal/thermal_zone0/temp`)/1000)" | bc)
diskwar=`echo $disk | tr "%" " " | awk '{if($2>=0&&$2<=80) printf("%s","normal");else if($2<=90) printf("%s","note"); else printf("%s","warning");}'`
cpuwar=`echo $Cputem | awk '{if($1>=0&&$1<=70) printf("%s","normal"); else if($1<=80) printf("%s","note"); else printf("%s","waring");}'`
memwar=`echo $mem | tr ",:%" " " | awk '{if($4>=0&&$4<=70) printf("%s","normal"); else if($4<=80) printf("%s","note"); else printf("%s","waring");}'`
echo "system"
echo "$date"
echo "$hostname $uname $utime $cpu $disk $mem $Cputem"
echo "硬盘:$diskwar CPU:$cpuwar 存储器:$memwar"
