default:
	cd oneTBB-tbb_2020 && $(MAKE)
	# LDFLAGS = -L. -loneTBB-tbb_2020
	# LDFLAGS = -static
	g++ quicksort.cpp -o quicksort

	./build_and_test.sh test1.txt 1

clean:
	rm quicksort
	cd oneTBB-tbb_2020 && $(MAKE) clean
