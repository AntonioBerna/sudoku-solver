#!/bin/sh

echo "" > "benchmarks-results.txt"

for i in {1..9};
do
	hyperfine --warmup 3 -N -i "./sudoku $i" >> "benchmarks-results.txt"
done
