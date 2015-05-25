#!/bin/bash

declare -a temp=("2.265" "2.266" "2.267" "2.268" "2.269")
L=1024
nblock=64
nsamp=1000


commando="./ising L=$L nblock=$nblock nsamp=$nsamp"
for T in "${temp[@]}"
do
	commando="$commando T=$T run"
done
echo $commando
eval $commando

