

cd ../Cluster
declare -a temp=("2.31" "2.285" "2.275")
declare -a size=("16" "32" "64" "128" "256")
nblock=64
nsamp=1000;

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

