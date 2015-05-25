#!/bin/bash


../Cluster/
declare -a temp=("1.8" "2.0" "2.2" "2.3" "2.4" "2.6" "2.8")
declare -a size=("32")
nblock=128000

nsamp=200

for L in "${size[@]}"
do
	for T in "${temp[@]}"
	do
		commando="./ising L=$L nblock=$nblock nsamp=$nsamp T=$T run"
		echo $commando
		eval $commando
	done
done

cd ../Metro/
declare -a temp=("1.8" "2.0" "2.2" "2.3" "2.4" "2.6" "2.8")
declare -a size=("32")
nblock=128000

nsamp=200

for L in "${size[@]}"
do
	for T in "${temp[@]}"
	do
		commando="./ising L=$L nblock=$nblock nsamp=$nsamp T=$T run"
		echo $commando
		eval $commando
	done
done
cd ../runs
