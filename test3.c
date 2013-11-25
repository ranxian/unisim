#include "stdlib.h"

int array[] = {2, 1, 5, 4, 3, 6};

void print_value()
{
	int i;
	for (i = 0; i < 6; i++)
		sys_putint(array[i]);
	sys_putint(12345);
}

int pivotLoc(int *arr, int bt, int ed)
{
	int stand;

	stand = arr[bt];

	while (bt < ed) {
		while (bt < ed && arr[ed] >= stand)   ed --;
		if (bt < ed) arr[bt ++] = arr[ed];

		while (bt < ed && arr[bt] <= stand)   bt ++;
		if (bt < ed) arr[ed --] = arr[bt];
	}

	arr[bt] = stand;

	return bt;
}

void quickSort(int *arr, int bt, int ed)
{
	print_value();
	int pivot;

	if (bt < ed) {
		pivot = pivotLoc(arr, bt, ed);
		quickSort(arr, bt, pivot - 1);
		quickSort(arr, pivot + 1, ed);
	}
}

int main()
{
	int i;
	quickSort(array, 0, 6);

	return array[0];
}
