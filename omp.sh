#/bin/bash

threads=(1 2 4 8 16 28)
txt=("100.txt" "500.txt" "1000.txt" "10000.txt" "50000.txt" "100000.txt" )

exec 4> resultsOmp.txt

for x in "${txt[@]}"
do
   for y in "${threads[@]}"
   do
	echo $x >&4
	./quicksort_omp $x $y >&4
   done
done 

exec 4<&-


