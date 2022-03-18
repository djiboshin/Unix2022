#!/bin/bash
if [ -n "$1" ]; then
	if ! [[ "$1" =~ ^[0-9]+$ ]]; then 
		echo "int only"
		exit 1
	else
		dir_name=$(printf "lab_%02d" $1)
		mkdir -p "$dir_name/src" && touch "$_/.gitkeep"
		mkdir -p "$dir_name/doc" && touch "$_/.gitkeep"
		mkdir -p "$dir_name/cmake" && touch "$_/.gitkeep"
		exit 0
	fi
else
	echo "1 int arg required"
fi
