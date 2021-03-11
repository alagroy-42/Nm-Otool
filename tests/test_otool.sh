#!/bin/bash

for i in `ls`; do
	echo processing $i
	otool -t $i > otool.dif 2>&-
	../ft_otool -t $i > mine.dif 2>&-
	diff -B otool.dif mine.dif
	if [ $? = 0 ]; then
		echo $i : SUCCESS !!
	else
		echo $i : FAILURE !!
		exit
	fi
done;

rm *.dif