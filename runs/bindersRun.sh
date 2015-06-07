

cd ../Cluster
declare -a temp=("2.20" "2.22" "2.24" "2.25" "2.26" "2.27" "2.275" "2.28" "2.285" "2.29" "2.30" "2.31" "2.32" "2.34" "2.36" "2.38" "2.40" "2.44" "2.48" "2.52" "2.56" "2.60" "2.70")
declare -a size=("16" "32" "64" "128" "256")

nsamp=1000;

commando="./ising"
for L in "${size[@]}"
do
	for T in "${temp[@]}"
	do
		commando="$commando L=$L binders=1 tcorr=1 nblock=$nblock nsamp=$nsamp T=$T run"
	done
done
echo $commando
sleep 5
eval $commando
cd ../runs

