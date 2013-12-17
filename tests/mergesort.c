#include "testheader.h"
#include "sort.h"
#define MUL 214013
#define ADD 2531011
#ifndef MAXN
#define MAXN 4
#endif
int seed = 234;

void merge(int arr[],int p,int q,int r)
{

	int A[MAXN],B[MAXN];
	int i = 0, j = 0, k;
	int n1 = q - p;
	int n2 = r - q;
	for (k = p; k < q; k++)
		A[i++] = arr[k];
	for (k = q; k < r; k++)
		B[j++] = arr[k];

	k = p;
	i = 0; j = 0;
	while (i < n1 && j < n2) {
		if (A[i] < B[j])
			arr[k++] = A[i++];
		else
			arr[k++] = B[j++];
	}
	while (i < n1)
		arr[k++] = A[i++];
	while (j < n2)
		arr[k++] = B[j++];
}

void mergeSort(int arr[],int begin,int end)
{
	int mid;
	if (begin + 1< end)
	{
		mid=(begin+end)/2;
		mergeSort(arr,begin,mid);
		mergeSort(arr,mid,end);
		merge(arr,begin,mid,end);
	}
}


int main()
{
	int array[MAXN];
	int i;
	for (i = 0; i < MAXN; i++) {
		seed = seed * MUL + ADD;
		array[i] = seed;
	}
	sys_state(0);
	mergeSort(array, 0, MAXN);
	sys_state(0);
	print(array);
	return 0;
}
