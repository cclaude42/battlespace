#!/bin/bash
cp btsp ..
cd ..

gcc -o battlespace battlespace.c

TOT=0
for i in {1..100}
do
	./map_gen.py > maps/map$i
	OUT=$(./battlespace maps/map$i btsp)
	TOT=$(( TOT+OUT ))
	echo $i $OUT
done
echo

TOT=$(( TOT/100 ))
echo $TOT

rm btsp
cd cclaude
