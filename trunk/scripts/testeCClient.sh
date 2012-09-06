#!/bin/bash 	

base=../
basepath=${base}doc/programsOut/
pathDocClient=${basepath}clients/
ipConnectionServerLevel2=("0" "localhost" "localhost")
binfolder=${base}bin/

portServer2=("0" "20003" "20003")

for i in `seq 1 2`; do
	echo Cliente C $i
	./${binfolder}clientC ${ipConnectionServerLevel2[$i]} ${portServer2[$i]} > ${pathDocClient}clientC$i.txt &
done

