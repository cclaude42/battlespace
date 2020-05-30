#!/bin/bash
make re
cp btsp ..

cd ..

gcc -o battlespace battlespace.c

TOT=0
for i in {1..10000}
do
	./map_gen.py > map
	OUT=$(./battlespace map btsp)
	TOT=$(( TOT+OUT ))
	if (( i % 100 == 0 ))
	then
		echo $i / 10000 tests
	fi
done
echo

echo $TOT
echo $(( TOT/10000 ))

rm btsp

cd cclaude
