#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

#define getClock() ((double)clock() / CLOCKS_PER_SEC)

static void import(char const * const filename, int * const np, int** const ap)
{
	int i, j, n, ret;
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

}

void quickSort(int *a, int lo, int hi)
{
	//printf("%d %d %d\n", a[0], lo, hi);
	int pivot;
	if (lo < hi)
	{
		pivot = partition(a, lo, hi);
	        #pragma omp task
		{
		quickSort(a, lo, pivot-1);
		}
		#pragma omp task
		{
		quickSort(a, pivot+1, hi);
		}
	}
}

int main(int argc, char **argv)
{
	int n, i, j, low, high;
	int *a;

	if(argc < 2)
	{
		return EXIT_FAILURE;
	}

	import(argv[1], &n, &a);
	low = 0;
	high = n;
	/*for(i = 0; i < n; i++)
	{
		printf("%d\n", a[i]);
	}*/
    	
	double start = getClock();
	#pragma omp parallel num_threads(4)
	{
	   #pragma omp single
	   {
		quickSort(a, low, high);
	   }
	}
	double end = getClock();
	for(i = 0; i < n; i++)
	{
		printf("%d\n", a[i]);
	}
 	printf("%f seconds\n", end - start);   
	return EXIT_SUCCESS;
}
