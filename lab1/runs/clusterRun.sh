#!/bin/bash
PATH_BINARY=../../src/Cluster
#from cluster binary
DATA_DIR=../../lab1/data/


declare -a temp=("2.20" "2.22" "2.24" "2.25" "2.255" "2.26" "2.262" "2.624" "2.266" "2.268" "2.269")
L=64
nblock=128
nsamp=1000

SCRIPT_DIR=`pwd`
cd $PATH_BINARY
commando="./cluster L=$L nblock=$nblock nsamp=$nsamp datadir=$DATA_DIR"
for T in "${temp[@]}"
do
	commando="$commando T=$T run"
done
echo $commando
eval $commando


declare -a temp=("2.20" "2.22" "2.24" "2.25" "2.255" "2.26" "2.262" "2.624" "2.266" "2.268" "2.269")
L=256
nblock=128
nsamp=1000


commando="./cluster L=$L nblock=$nblock nsamp=$nsamp datadir=$DATA_DIR"
for T in "${temp[@]}"
do
	commando="$commando T=$T run"
done
echo $commando
eval $commando



declare -a temp=("2.265" "2.266" "2.267" "2.268" "2.269" "2.24" "2.25" "2.255" "2.26" "2.262")
L=1024
nblock=64
nsamp=1000


commando="./cluster L=$L nblock=$nblock nsamp=$nsamp datadir=$DATA_DIR"
for T in "${temp[@]}"
do
	commando="$commando T=$T run"
done
echo $commando
eval $commando
