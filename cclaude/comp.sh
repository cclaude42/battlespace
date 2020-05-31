#!/bin/bash
make re
cp btsp ..

cd ..

gcc -o battlespace battlespace.c

TOT=0
TOT2=0
for i in {1..1000}
do
	./map_gen.py > maps/map$i
	OUT=$(./battlespace maps/map$i btsp)
	OUT2=$(./battlespace maps/map$i btsp+x)
	TOT=$(( TOT+OUT ))
	TOT2=$(( TOT2+OUT2))
	echo $i $((OUT-OUT2))
done
echo

echo BEFORE : $TOT
echo AFTER : $TOT2

rm btsp

cd cclaude
