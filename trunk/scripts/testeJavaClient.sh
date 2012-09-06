#!/bin/bash 	

basepath=doc/programsOut/
pathDocClient=${basepath}clients/
ipConnectionServerLevel2=("0" "172.27.115.100" "172.27.115.100" "172.27.115.100" "172.27.115.100")
binfolder=bin/

portServer2=("0" "51001" "51001" "51002" "51002")

for i in `seq 1 4`; do
	echo Cliente Java $i
	javac $(binfolder)Client ${ipConnectionServerLevel2[$i]} ${portServer2[$i]} > ${pathDocClient}clientJava$i.txt &
done

