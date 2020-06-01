#/bin/bash

threads=(1 2 3 4 5 6 7 8)
txt=("1000.txt" "5000.txt" "10000.txt" "50000.txt" "100000.txt" "500000.txt" "1000000.txt" )

exec 4> resultsOmp.txt

for x in "${txt[@]}"
do
   echo $x >&4
   for y in "${threads[@]}"
   do
	#echo $x >&4
	./quicksort_omp $x $y >&4
   done
done 

exec 4<&-


