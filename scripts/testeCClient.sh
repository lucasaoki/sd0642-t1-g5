#!/bin/bash 	

basepath=doc/programsOut/
pathDocClient=${basepath}clients/
ipConnectionServerLevel2={"0" "localhost" "localhost"}
binfolder=bin/


portServer2=("0" "51000" "51000")

for i in `seq 1 2`; do
	echo Cliente C $i
	./${binfolder}clientC ${ipConnectionServerLevel2[$i]} ${portServer2[$i]} > ${pathDocClient}clientC$i.txt &
done

