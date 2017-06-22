#!/bin/bash
PATH_BINARY=../../src/Metro
#from cluster binary
DATA_DIR=../../lab1/data/metro

SCRIPT_DIR=`pwd`
cd $PATH_BINARY

declare -a temp=("2.0" "2.1" "2.2")
L=16
nblock=64

for T in "${temp[@]}"
do
	commando="./metro L=$L nblock=$nblock T=$T datadir=$DATA_DIR run"
	echo $commando
	eval $commando
done
cd $SCRIPT_DIR

