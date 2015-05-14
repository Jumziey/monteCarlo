#!/bin/bash

declare -a temp=("2.20" "2.22" "2.24" "2.25" "2.255" "2.26" "2.262" "2.624" "2.266" "2.268" "2.269")
L=64
nblock=1


for T in "${temp[@]}"
do
	commando="./ising L=$L ntherm=1000 nblock=$nblock T=$T run"
	echo $commando
	eval $commando
done


