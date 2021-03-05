#!/bin/zsh
for file in $@ /bin/* /sbin/* /usr/bin/* /usr/sbin/* /usr/lib/* /usr/lib/*/* /usr/libexec/* /usr/libexec/*/* /usr/share/*
do
	echo "diff on $file"
	otool -t $file > resotool 2> errotool
	../ft_otool $file > resftotool 2> errftotool
	diff resotool resftotool
done
