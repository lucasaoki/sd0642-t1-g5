#!/bin/bash 	

base=../
basepath=${base}doc/programsOut/
pathDocClient=${basepath}clients/
ipConnectionServerLevel2=("0" "localhost" "localhost" "localhost" "localhost")
binfolder=${base}bin/

portServer2=("0" "20001" "20001" "20002" "20002")

for i in `seq 1 4`; do
	echo Cliente Java $i
	java -cp ${binfolder} Client ${ipConnectionServerLevel2[$i]} ${portServer2[$i]} > ${pathDocClient}clientJava$i.txt &
done

