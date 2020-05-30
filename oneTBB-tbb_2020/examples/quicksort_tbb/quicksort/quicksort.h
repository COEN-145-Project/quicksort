#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../common/utility/get_default_num_threads.h"
#include <cstddef>

// void import(char const * const filename, int * const np, int** const ap);
int partition(int *a, int lo, int hi);
void quickSort(int *a, int lo, int hi);
int quickSortMain(char * fileName, int thread_count);