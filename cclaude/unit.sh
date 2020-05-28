#!/bin/bash
make re
cp btsp ..

cd ..

mkdir maps
gcc -o battlespace battlespace.c

TOT=0
for i in {1..100}
do
	OUT=$(./battlespace maps/map$i btsp)
	TOT=$(( TOT+OUT ))
	echo $i $OUT
done
echo

TOT=$(( TOT ))
echo $TOT

rm btsp

cd cclaude
