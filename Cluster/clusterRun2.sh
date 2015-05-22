#!/bin/bash

declare -a temp=("2.265" "2.266" "2.267" "2.268" "2.269")
L=1024
nblock=64
nsamp=1000


for T in "${temp[@]}"
do
	commando="./ising L=$L ntherm=1000 nblock=$nblock nsamp=$nsamp T=$T run"
	echo $commando
	eval $commando
done


