#!/bin/bash 	

base=../
basepath=${base}doc/programsOut/
pathDocServer=${basepath}servers/
ipConnectionServerFinal=172.26.413.113
ipConnectionServerLevel3="localhost"
binfolder=${base}bin/

sleep 1
#Servidores level 3
portServer4="40000"
portMyServer1="30001"	

echo Server 1 Level 3 
./${binfolder}serverInterCpp ${portMyServer1} 3 ${ipConnectionServerLevel3} ${portServer4} > ${pathDocServer}serverCpp1Level3.txt &

sleep 1

#Servidores level 2
portServer1=("0" "30001" "30001")
portMyServer2=("0" "20002" "20003")

for i in `seq 1 2`; do
	echo Server $i Level 2
	./${binfolder}serverInterCpp ${portMyServer2[$i]} 2 ${ipConnectionServerLevel3[$i]} ${portServer1[$i]} > ${pathDocServer}serverCpp${i}Level2.txt &
done 
