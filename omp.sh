#/bin/bash

threads=(1 2 4 8 16 28)
txt=("1000.txt" "5000.txt" "10000.txt" "50000.txt" "100000.txt" "500000.txt" "1000000.txt" )

exec 4> resultsOmp2.txt

for x in "${txt[@]}"
do
   echo $x >&4
   for y in `seq 1 28` 
   do
	#echo $x >&4
	./quicksort_omp $x $y >&4
   done
done 

exec 4<&-


