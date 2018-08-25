#!/bin/bash 
Nowdate=`date -u +"%Y-%m-%d__%H:%M:%S"`
num=`cat /etc/passwd | awk -F: -v sum=0 '{if($3>=1000&&$3!=65534) sum+=1;} END {print sum}'`
totaluser=`last |tr -s "\n" | cut -d ' ' -f1 | sort | uniq -c | grep -v wtmp | awk '{printf("%s ",$2);}'`
Nowsu=`cat /etc/group | grep sudo | awk -F: '{print $4}'`
Nowsu+=" "
Nowuser=`w | sed "1,2d" | awk '{print $1,$2,$3}'`
Nowsu+=`cat /home/sudoers | grep "ALL=(ALL:ALL)" | tr "\t " ":" | awk -F: '{printf("%s ",$1);}'`
echo "User Log" >> UserLog
echo "$Nowdate 总人次:$num $totaluser root:$Nowsu" >> UserLog
echo "最近登录前三:$Nowuser" >> UserLog
