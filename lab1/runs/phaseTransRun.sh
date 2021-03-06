#!/bin/bash
PATH_BINARY=../../src/Metro
#from cluster binary
DATA_DIR=../../lab1/data/metro

SCRIPT_DIR=`pwd`
cd $PATH_BINARY
declare -a temp=("2.0" "2.1" "2.16" "2.18" "2.20" "2.22" "2.24" "2.25" "2.26" "2.27" "2.28" "2.29" "2.30" "2.32" "2.34" "2.36" "2.38" "2.40" "2.44" "2.48" "2.52" "2.56" "2.60" "2.70")
declare -a size=("8" "16" "32" "64")
nblock=256
nsamp=100

for L in "${size[@]}"
do
	for T in "${temp[@]}"
	do
		commando="./metro L=$L nblock=$nblock nsamp=$nsamp T=$T datadir=$DATA_DIR run"
		echo $commando
		eval $commando
	done
done
cd $SCRIPT_DIR

