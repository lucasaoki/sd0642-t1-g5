#!/bin/bash 	

base=../
basepath=${base}doc/programsOut/
pathDocClient=${basepath}clients/
ipConnectionServerLevel2=("0" "localhost" "localhost")
binfolder=${base}bin/

portServer2=("0" "20000" "20000")

for i in `seq 1 2`; do
	echo Cliente Cpp $i
	./${binfolder}clientCpp ${ipConnectionServerLevel2[$i]} ${portServer2[$i]} > ${pathDocClient}clientCpp$i.txt &
done

