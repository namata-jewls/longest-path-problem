#!/bin/bash

# compile
gcc -o bf brute-force.c
gcc -o nbf non-brute-force.c

# clean previous logs
rm -f bf.out nbf.out bfs.out nbfs.out

# Run brute-force version
echo "Running brute force algorithm"
for (( i = 1; i < 4; i++ )); do
	echo "========================" >> bf.out
	echo "run: $i" | tee -a bf.out
	for (( j = 4; j < 25; j+=4 )); do
		echo "vertices: $j" | tee -a bf.out
		./bf tests/dense/$j.in | tee -a bf.out
		echo | tee -a bf.out
	done
	echo "========================"
done

# Run non-brute-force version
echo "Running non brute force algorithm"
for (( i = 1; i < 4; i++ )); do
	echo "========================" >> nbf.out
	echo "run: $i" | tee -a nbf.out
	for (( j = 4; j < 25; j+=4 )); do
		echo "vertices: $j" | tee -a nbf.out
		./nbf tests/dense/$j.in | tee -a nbf.out
		echo | tee -a nbf.out
	done
	echo "========================"
done

# Run brute-force version
echo "Running brute force algorithm"
for (( i = 1; i < 4; i++ )); do
	echo "========================" >> bfs.out
	echo "run: $i" | tee -a bfs.out
	for (( j = 4; j < 25; j+=4 )); do
		echo "vertices: $j" | tee -a bfs.out
		./bf tests/sparse/$j.in | tee -a bfs.out
		echo | tee -a bfs.out
	done
	echo "========================"
done

# Run non-brute-force version
echo "Running non brute force algorithm"
for (( i = 1; i < 4; i++ )); do
	echo "========================" >> nbfs.out
	echo "run: $i" | tee -a nbfs.out
	for (( j = 4; j < 25; j+=4 )); do
		echo "vertices: $j" | tee -a nbfs.out
		./nbf tests/sparse/$j.in | tee -a nbfs.out
		echo | tee -a nbfs.out
	done
	echo "========================"
done