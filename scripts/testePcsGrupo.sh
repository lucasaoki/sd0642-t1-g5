#!/bin/bash 	

basepath=doc/programsOut/
pathDocServer=${basepath}servers/
pathDocClient=${basepath}clients/
ipConnectionServerFinal=172.26.413.113


echo 'Start: Trabalho de SD'


#Servidor Principal
#echo 'main'
#./serverMain 41000 > ${pathDocServer}main.txt &

sleep 1
#Servidores level 3
portServer0=41000
portMyServer1=("0" "41001" "41002")	

for i in `seq 1 2`; do
	echo Server $i Level 3 
	./server ${portMyServer1[$i]} 3 ${ipConnectionServerFinal} ${portServer0} > ${pathDocServer}server${i}Level3.txt &
done 

sleep 1

#Servidores level 2
portServer1=("0" "41001" "41001" "41002" "41002")
portMyServer2=("0" "41003" "41004" "41005" "41006")

for i in `seq 1 4`; do
	echo Server $i Level 2
	./server ${portMyServer2[$i]} 2 localhost ${portServer1[$i]} > ${pathDocServer}server${i}Level2.txt &
done 



sleep 1


portServer2=("0" "41003" "41003" "41004" "41004" "41005" "41005" "41006" "41006")

for i in `seq 1 8`; do
	echo Cliente $i
	./client localhost ${portServer2[$i]} > ${pathDocClient}client$i.txt &
done

sleep 1
