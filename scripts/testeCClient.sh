#!/bin/bash 	

base=../
basepath=${base}doc/programsOut/
pathDocClient=${basepath}clients/
ipConnectionServerLevel2="localhost"
binfolder=${base}bin/

portServer2="20003"

for i in `seq 1 2`; do
	echo Cliente C $i
	./${binfolder}clientC ${ipConnectionServerLevel2} ${portServer2} > ${pathDocClient}clientC$i.txt &
done

