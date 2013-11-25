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
	int pivot;

	if (bt < ed) {
		pivot = pivotLoc(arr, bt, ed);
		quickSort(arr, bt, pivot - 1);
		quickSort(arr, pivot + 1, ed);
	}
}

int main()
{
	int array[] = {2, 1, 5, 4, 3};
	quickSort(array, 0, 5);
	return array[0];
}
