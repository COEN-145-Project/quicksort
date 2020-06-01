#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

#define getClock() ((double)clock() / CLOCKS_PER_SEC)

void quickSort_parallel(int* array, int lenArray, int numThreads);
void quickSort_parallel_internal(int* array, int left, int right, int cutoff);

static void import(char const * const filename, int * const np, int** const ap)
{
	int i, n, ret;
	FILE *fp;
	float *a;
	fp = fopen(filename, "r");
    
	ret = fscanf(fp, "%d", &n);

	a = malloc(n*sizeof(*a));

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

	/*int i = lo, j = hi;
	int tmp;
	while(i <= j)
	{
		while(a[i] < pivot)
*/
}

void quickSort(int *a, int lo, int hi)
{
	//printf("%d %d %d\n", a[0], lo, hi);
	int pivot;
	if (lo < hi)
	{
		pivot = partition(a, lo, hi);
		if((hi - lo) > 1000)
		{	
	        #pragma omp task
		{
		quickSort(a, lo, pivot-1);
		}
		#pragma omp task
		{
		quickSort(a, pivot+1, hi);
		}
		}
		else
		{
		   quickSort(a, lo, pivot-1);
		   quickSort(a, pivot+1, hi);
		}
		
		}
}

int main(int argc, char **argv)
{
	int n, i, low, high;
	int *a;

	if(argc < 3)
	{
		printf("./quicksort_omp testfile.txt numThreads\n");
		return EXIT_FAILURE;
	}

	import(argv[1], &n, &a);
	low = 0;
	high = n;
	int numThreads = atoi(argv[2]);
	/*for(i = 0; i < n; i++)
	{
		printf("%d\n", a[i]);
	}*/
    	
	double start = omp_get_wtime();
	#pragma omp parallel num_threads(numThreads)
	{
	   #pragma omp single nowait
	   {
		quickSort(a, low, high);
		//quickSort(a,low, high, numThreads);
	   }
	}
	double end = omp_get_wtime();
	/*for(i = 0; i < n; i++)
	{
		printf("%d\n", a[i]);
	}*/
 	printf("%.3f\n", (end - start)*1000);   
	return EXIT_SUCCESS;
}
