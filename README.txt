README

To make OMP:
Call "make omp" on hpc

To make TBB local:
Call "make tbb_local"

To make TBB HPC:
Start slurm session
Load tbb module
Call "make tbb_hpc"

All versions of quicksort can be called with 2 parameters, first being the file to sort and second being the max thread count
EX: ./quicksort_omp test1.txt 6
EX: ./quicksort 100.txt 5
EX: ./oneTBB-tbb_2020/examples/quicksort_tbb/quicksort/quicksort 1000.txt 8