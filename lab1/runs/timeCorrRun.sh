#!/bin/bash
PATH_BINARY=../../src/Cluster
#from cluster binary
DATA_DIR=../../lab1/data/cluster

SCRIPT_DIR=`pwd`
cd $PATH_BINARY
declare -a temp=("1.8" "2.0" "2.2" "2.3" "2.4" "2.6" "2.8")
declare -a size=("32")
nblock=12800

nsamp=200

for L in "${size[@]}"
do
	for T in "${temp[@]}"
	do
		commando="./cluster L=$L nblock=$nblock nsamp=$nsamp T=$T datadir=$DATA_DIR run"
		echo $commando
		eval $commando
	done
done
cd $SCRIPT_DIR
