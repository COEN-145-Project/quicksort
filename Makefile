default:
	cd oneTBB-tbb_2020 && $(MAKE)
	# LDFLAGS = -L. -loneTBB-tbb_2020
	# LDFLAGS = -static
	g++ quicksort.cpp -o quicksort

clean:
	rm quicksort
	cd oneTBB-tbb_2020 && $(MAKE) clean
