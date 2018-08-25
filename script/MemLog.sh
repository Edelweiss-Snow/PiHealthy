#!/bin/bashi 
MemValue=(`free -m | head -n 2 | tail -n 1 | awk '{printf("%s %s\n",$2,$3)}'`)
MemAvaPrec=`echo "scale=1;${MemValue[1]}*100/${MemValue[0]}" | bc`
NowAver=`echo "scale=1;0.8*${MemAvaPrec}+0.2*${DyAver}" | bc`


NowTime=`date +"%Y-%m-%d__%H:%M:%S"`
echo "MemLog" >> MemLog
echo "$NowTime" >> MemLog
echo "total:${MemValue[0]}M used:${MemValue[1]}M 占用率:${MemAvaPrec}% ${NowAver}" >> MemLog
