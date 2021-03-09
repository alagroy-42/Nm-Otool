#!/bin/bash

for i in /bin/* /usr/bin/*; do
	echo processing $i
	nm $i > nm.dif 2>&-
	../ft_nm $i > mine.dif 2>&-
	diff -B nm.dif mine.dif
	if [ $? = 0 ]; then
		echo $i : SUCCESS !!
	else
		echo $i : FAILURE !!
		exit
	fi
done;

rm *.dif