#!/bin/bash

#Heat capacity check
declare -a temp=("2.0" "2.1" "2.2")
L=16
nblock=64

for T in "${temp[@]}"
do
	commando="./ising L=$L nblock=$nblock T=$T run"
	echo $commando
	eval $commando
done

