#!/bin/bash 	
base=../
basepath=${base}doc/programsOut/
pathDocServer=${basepath}servers/
ipConnectionServerFinal=172.26.413.113
ipConnectionServerLevel3=("0" "localhost" "localhost")
binfolder=${base}bin/

sleep 1
#Servidores level 3
portServer4="40000"
portMyServer1="30000"	

echo Server 1 Level 3 
./${bin}serverC ${portMyServer1} 3 ${ipConnectionServerFinal} ${portServer4} > ${pathDocServer}serverC${i}Level3.txt &


sleep 1

#Servidores level 2
portServer1=("0" "30000" "30000")
portMyServer2=("0" "20000" "20001")

for i in `seq 1 2`; do
	echo Server $i Level 2
	./${bin}serverC ${portMyServer2[$i]} 2 ${ipConnectionServerLevel3[$i]} ${portServer1[$i]} > ${pathDocServer}serverC${i}Level2.txt &
done 
