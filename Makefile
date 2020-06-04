default:
	cd oneTBB-tbb_2020 && $(MAKE)
	# LDFLAGS = -L. -loneTBB-tbb_2020
	# LDFLAGS = -static
	g++ quicksort.cpp -o quicksort
	gcc -fopenmp -o quicksort_omp quicksort_omp.c

run_tbb:
	./build_and_test.sh test1.txt 1

run_omp:
	./quicksort_omp test1.txt 1


clean:
	rm quicksort_omp
	rm quicksort
	cd oneTBB-tbb_2020 && $(MAKE) clean
