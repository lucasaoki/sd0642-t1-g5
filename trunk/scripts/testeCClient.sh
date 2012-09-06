#!/bin/bash 	

basepath=doc/programsOut/
pathDocClient=${basepath}clients/
ipConnectionServerLevel2={"0" "localhost" "localhost" "localhost" "localhots"}
binfolder=bin/


portServer2=("0" "51003" "51003" "51004" "51004" "51005" "51005" "51006" "51006")

for i in `seq 1 4`; do
	echo Cliente $i
	clientC $(binfolder)Cliente ${ipConnectionServerLevel2[$i]} ${portServer2[$i]} >> ${pathDocClient}clientC$i.txt &
done

