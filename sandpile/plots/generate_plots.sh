#!/bin/bash

declare -a scripts=(
	"AvalancheSize.py"
	"AvalancheTime.py"
	"ValueAnalysis.py"
	"SizeFit.py"
)

for script in "${scripts[@]}"
do
	eval "python3 $script"
done
