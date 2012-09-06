#!/bin/bash 	
base=../
basepath=${base}doc/programsOut/
pathDocServer=${basepath}servers/
ipConnectionServerFinal="172.27.122.131"
ipConnectionServerLevel3=("0" "localhost" "localhost" "localhost" "localhost")
binfolder=${base}bin/

sleep 1
#Servidores level 3
portServer4=("0" "40000" "40000")
portMyServer1=("0" "30000" "30001")	
for i in `seq 1 1`; do
	echo Server C $i Level 3 
	./${binfolder}serverC ${portMyServer1[$i]} 3 ${ipConnectionServerFinal} ${portServer4[$i]} > ${pathDocServer}serverC1Level3.txt &
done

sleep 1

#Servidores level 2
portServer1=("0" "30000" "30000" "30001" "30001")
portMyServer2=("0" "20000" "20001" "20002" "20003")

for i in `seq 1 2`; do
	echo Server C $i Level 2
	./${binfolder}serverC ${portMyServer2[$i]} 2 ${ipConnectionServerLevel3[$i]} ${portServer1[$i]} > ${pathDocServer}serverC${i}Level2.txt &
done 
