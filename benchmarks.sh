#!/bin/sh

truncate -s 0 "benchmarks.md"

for i in {1..9}; do
	hyperfine --warmup 3 --export-markdown "temp.md" -N -i "./sudoku $i"

	cat temp.md >> "benchmarks.md"
	echo "" >> "benchmarks.md"
done

rm temp.md
