#include "quicksort.h"

#include <unistd.h>

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <math.h>
#include <cstdlib>
#include <cctype>
#include "tbb/parallel_reduce.h"
#include "tbb/parallel_invoke.h"

#include "tbb/tick_count.h"

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

int partition(int *a, int lo, int hi)
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

void quickSort(int *a, int lo, int hi)
{
	//printf("%d %d %d\n", a[0], lo, hi);
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

int quickSortMain(char * fileName, int thread_count)
{
	int n, i, j, low, high;
	int *a;

	// if(argc < 3)
	// {
	// 	return EXIT_FAILURE;
	// }

    printf("running with %d threads\n", thread_count);
	import(fileName, &n, &a);
	low = 0;
	high = n;
	/*for(i = 0; i < n; i++)
	{
		printf("%d\n", a[i]);
	}*/

    // tbb::parallel_invoke(
    //     [&]{print1();},
    //     [&]{print2();}
    // );

    // test line
    
    tbb::global_control c(tbb::global_control::max_allowed_parallelism, thread_count);
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

int main (int argc, char **argv)
{
	if(argc != 3)
	{
		printf("missing args!\n");
		return -1;
	}

	char * fileName = argv[1];
	uint fileSize = atoi(argv[2]);
	quickSortMain(fileName, fileSize);

	return 0;
}


