#!/bin/bash 
DyAver=$1
MemValue=(`free -m | head -n 2 | tail -n 1 | awk '{printf("%s %s\n",$2,$3)}'`)
MemAvaPrec=`echo "scale=1;${MemValue[1]}*100/${MemValue[0]}" | bc`
NowAver=`echo "scale=1;0.8*${MemAvaPrec}+0.2*${DyAver}" | bc`
mem=`free -m | sed -n '2p' | awk '{printf("total:%d,used:%.4f%%",$2,$3/$2*100)}'`
memwar=`echo $mem | tr ",:%" " " | awk '{if($4>=0&&$4<=70) printf("%s","1"); else if($4<=80) printf("%s","2"); else printf("%s","3");}'`

NowTime=`date +"%Y-%m-%d__%H:%M:%S"`
echo "MemLog"
echo "$NowTime"
echo "total:${MemValue[0]}M used:${MemValue[1]}M 占用率:${MemAvaPrec}% ${NowAver}"
echo "signal" $memwar $MemAvaPrec 
