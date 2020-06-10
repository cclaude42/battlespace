#!/bin/bash
make -C cclaude
gcc -o battlespace battlespace.c

TOT=0
for i in {1..10000}
do
	./map_gen.py > map
	OUT=$(./battlespace map cclaude/btsp)
	TOT=$(( TOT+OUT ))
	if (( i % 100 == 0 ))
	then
		echo $i / 10000 tests
	fi
done
echo
rm map

echo $TOT "("$(( TOT/10000 ))")"
