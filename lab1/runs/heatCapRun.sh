#!/bin/bash

cd ../Metro
#Heat capacity check
declare -a temp=("2.0" "2.1" "2.2")
L=16
nblock=64
nsamp=10000;

for T in "${temp[@]}"
do
	commando="./ising L=$L nblock=$nblock nsamp=$nsamp T=$T run"
	echo $commando
	eval $commando
done
cd ../runs

