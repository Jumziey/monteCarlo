#!/bin/bash

a=1000000
declare -a length=("32")


SCRIPT_DIR=`pwd`
cd ../src/

commando="./sandpile"
for L in "${length[@]}"
do
	args="-L=$L -a=$a"
	run="$commando $args"
	eval $run
	echo "just ran: $run"
done

cd $SCRIPT_DIR

