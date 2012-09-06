#!/bin/bash 	

basepath=doc/programsOut/
pathDocClient=${basepath}clients/
ipConnectionServerLevel2={"0" "localhost" "localhost" "localhost" "localhots"}
binfolder=bin/


portServer2=("0" "41003" "41003" "41004" "41004" "41005" "41005" "41006" "41006")

for i in `seq 1 4`; do
	echo Cliente $i
	javac $(binfolder)Cliente ${ipConnectionServerLevel2[$i]} ${portServer2[$i]} >> ${pathDocClient}clientJava$i.txt &
done

