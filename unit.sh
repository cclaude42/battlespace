#!/bin/bash
make -C cclaude
gcc -o battlespace battlespace.c
rm -rf maps
mkdir maps

TOT=0
for i in {1..100}
do
	./map_gen.py > maps/map$i
	OUT=$(./battlespace maps/map$i cclaude/btsp)
	TOT=$(( TOT+OUT ))
	echo $i $OUT
done
echo

echo $TOT "("$(( TOT/100 ))")"
