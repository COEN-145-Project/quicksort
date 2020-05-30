#!/bin/bash

cd oneTBB-tbb_2020/examples && make

cd ../..

pwd

./oneTBB-tbb_2020/examples/quicksort_tbb/quicksort/quicksort $1 $2