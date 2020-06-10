#!/bin/bash
make -C cclaude
gcc -o battlespace battlespace.c

TOT=0
for i in {1..1000}
do
	./map_gen.py > map
	OUT=$(./battlespace map cclaude/btsp)
	TOT=$(( TOT+OUT ))
	if (( OUT > 99 ))
	then
		echo -n x
	else
		echo -n .
	fi
done
echo
rm map

echo $TOT "("$(( TOT/1000 ))")"
