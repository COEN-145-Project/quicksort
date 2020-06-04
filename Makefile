omp:
	gcc -fopenmp -o quicksort_omp quicksort_omp.c

tbb_hpc:
	cd itbb && $(MAKE)

tbb_local:
	cd oneTBB-tbb_2020 && $(MAKE)
	cd oneTBB-tbb_2020/examples && $(MAKE)

run_omp:
	./quicksort_omp test1.txt 1

run_tbb_hpc:
	./quicksort test1.txt 1

run_tbb_local:
	./oneTBB-tbb_2020/examples/quicksort_tbb/quicksort/quicksort
	
clean:
	rm quicksort_omp
	rm quicksort
	cd oneTBB-tbb_2020 && $(MAKE) clean

