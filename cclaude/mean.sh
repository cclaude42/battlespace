#!/bin/bash
make re
cp btsp ..

cd ..

gcc -o battlespace battlespace.c

TOT=0
for i in {1..1000}
do
	./map_gen.py > map
	OUT=$(./battlespace map btsp)
	TOT=$(( TOT+OUT ))
	if (( OUT > 99 ))
	then
		echo -n x
	else
		echo -n .
	fi
done
echo

echo $TOT
echo $(( TOT/1000 ))

rm btsp

cd cclaude
