PATH_BINARY=../../src/Cluster
#from cluster binary
DATA_DIR=../../lab2/data

SCRIPT_DIR=`pwd`
cd $PATH_BINARY
declare -a temp=("2.20" "2.22" "2.24" "2.25" "2.26" "2.265" "2.266" "2.267" "2.268" "2.269" "2.27" "2.271" "2.272" "2.275" "2.28" "2.285" "2.29" "2.30" "2.31" "2.32" "2.34" "2.36" "2.38" "2.40" "2.44" "2.48" "2.52" "2.56" "2.60" "2.70")
declare -a size=("16" "32" "64" "128" "256")

nsamp=1000;
binders=1;
nblock=64;

commando="./cluster"
for L in "${size[@]}"
do
	for T in "${temp[@]}"
	do
		run="L=$L binders=$binders nblock=$nblock nsamp=$nsamp T=$T datadir=$DATA_DIR run"
		commando="$commando $run"
		echo $run
	done
done
eval $commando
cd $SCRIPT_DIR

