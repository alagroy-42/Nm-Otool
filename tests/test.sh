#!/bin/bash

rm *.dif

for i in `ls`; do
	echo processing $i
	nm $i > $i.nm.dif
	../ft_nm $i > $i.mine.dif
	diff -B $i.nm.dif $i.mine.dif
	if [ $? = 0 ]; then
		echo $i : SUCCESS !!
	else
		echo $i : FAILURE !!
		exit
	fi
done;

rm *.dif