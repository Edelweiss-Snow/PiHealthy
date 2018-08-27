#!/bin/bash
NowTime=`date +"%Y-%m-%d__%H:%M:%S"`

eval $(df -T -m -x tmpfs -x devtmpfs | tail -n +2 | grep "dev" | \
    awk -v DiskSum=0 -v LeftSum=0 '{printf("paramount["NR"]=%d;parleft["NR"]=%d;parname[NR]=%s;\
    usedperc[NR]=%s;",$3,$5,$7,$6);DiskSum=DiskSum+$3;LeftSum=LeftSum+$5} \
    END {printf("parnum=%d;DiskSum=%d;LeftSum=%d",NR,DiskSum,LeftSum)}')
echo "DiskLog"
for (( i=1; i<=$parnum; i++ )); do
    echo "$NowTime 1 ${parname[$i]} ${paramount[$i]} ${parleft[$i]}\
    ${usedperc[$i]}"
done
disk=`df -m | tr -s " " | sed "1,1d" | head -1 | awk '{print $2,$5}'`
diskwar=`echo $disk | tr "%" " " | awk '{if($2>=0&&$2<=80) printf("%s","1");else if($2<=90) printf("%s","2"); else printf("%s","3");}'`

UsedPercSum=$[ (100-$LeftSum*100/$DiskSum) ]
echo "$NowTime 0 DiskSum $LeftSum ${UsedPercSum}%"
echo "signal" $diskwar $UsedPercSum
