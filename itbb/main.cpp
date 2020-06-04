/*
    Copyright (c) 2005-2020 Intel Corporation

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

// #include "primes.h"
// #include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #include "../../common/utility/get_default_num_threads.h"
#include <cstddef>

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <utility>
#include <iostream>
#include <sstream>
// #include "tbb.h"
#include "tbb/tick_count.h"
// #include "tbb/parallel_reduce.h"
#include "tbb/global_control.h"
#include "tbb/parallel_invoke.h"
// #include "tbb/task_scheduler_init.h"

// module load tbb/2019_U4-GCCcore-8.2.0
// srun --nodes 1 --ntasks 1 --cpus-per-task 1 --pty /bin/bash



using namespace std;

static void import(char const * const filename, int * const np, int** const ap)
{
	int i, j, n, ret;
	FILE *fp;
	int *a;
	fp = fopen(filename, "r");
    
	ret = fscanf(fp, "%d", &n);

	a = (int *)malloc(n*sizeof(*a));

	for( i = 0; i < n; i++)
	{
		ret = fscanf(fp, "%d", &a[i]);
	}
	fclose(fp);
	*np = n;
	*ap = a;
}

static int partition(int *a, int lo, int hi)
{
	int i, j;
	i = lo;
	for(j = lo; j < hi; ++j)
	{
		if(a[j] < a[hi])
		{
			int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			++i;
		}
	}
	
	int tmp2 = a[i];
	a[i] = a[hi];
	a[hi] = tmp2;

	return i;
}

static void print1()
{
    printf("test1\n");
    sleep(1);
    printf("test3\n");
}

static void print2()
{
    printf("test2\n");
    sleep(1);
    printf("test4\n");
}

static void quickSort(int *a, int lo, int hi)
{
	// printf("%d %d %d\n", a[0], lo, hi);
	int pivot;
	if (lo < hi)
	{
		pivot = partition(a, lo, hi);
        tbb::parallel_invoke(
        [&]{quickSort(a, lo, pivot-1);},
        [&]{quickSort(a, pivot+1, hi);}
    );
		// quickSort(a, lo, pivot-1);
		// quickSort(a, pivot+1, hi);
	}
}


int quickSortMain(char * fileName, int thread_count)
{
	int n, i, j, low, high;
	int *a;

    // const size_t parallelism = tbb::task_scheduler_init::default_num_threads();

    // printf("default thread count is %d\n", parallelism);

	// if(argc < 3)
	// {
	// 	return EXIT_FAILURE;
	// }

    // printf("running with %d threads\n", thread_count);
    tbb::global_control c(tbb::global_control::max_allowed_parallelism, thread_count);
	import(fileName, &n, &a);
	low = 0;
	high = n;
	/*for(i = 0; i < n; i++)
	{
		printf("%d\n", a[i]);
	}*/

    // tbb::parallel_invoke(
    //     [&]{print2();},
    //     [&]{print1();}
    // );


    // tbb::parallel_invoke(
    //     print1,
    //     print2
    // );

    // test line
    
    
    // tbb::task_scheduler_init(28);
    tbb::tick_count start_time = tbb::tick_count::now();
	quickSort(a, low, high);
    tbb::tick_count end_time = tbb::tick_count::now();

    // cout << "That took: " << (end_time-start_time).seconds() << "seconds\n"};

    printf("That took %f seconds\n", (end_time-start_time).seconds());

	// for(i = 0; i < n; i++)
	// {
	// 	printf("%d\n", a[i]);
	// }
    
	return EXIT_SUCCESS;
}



int main(int argc, char **argv)
{

    // printf("Main called\n");

    if(argc < 3)
	{
        printf("missing args\n");
		return EXIT_FAILURE;
	}


    char * fileName = argv[1];
    uint fileSize = atoi(argv[2]);
    
	quickSortMain(fileName, fileSize);
    
	return EXIT_SUCCESS;
}


