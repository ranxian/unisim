// qsort test
#include "testheader.h"
#define MAXN 1
#define MUL 214013
#define ADD 2531011
int seed = 234;


void print(int *array)
{
    int i;
    for (i = 0; i < MAXN; i++) {
        sys_putint(array[i]);
    }
}

void swap(int *array, int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int partition(int array[],int left, int right)
{
    //p <- Get a number from array
    int p=array[left];
    //Put elements < p to the left side
    //Put elements >= p to the right side
    int i=left,j;
    for(j=left+1;j<=right;j++)
    {
        if(array[j]<p)
        {
            i++;
            swap(array,i,j);
        }
    }
    //Put p in the middle slot which index is pivot
    swap(array,i,left);
    return i;
}

void quicksort(int array[], int left, int right)
{
    //Do nothing if left <= right
    print(array);
    if(left<right)
    {
        int pivot=partition(array,left,right);
        //Recursive quicksort the left parts and right parts
        quicksort(array,left,pivot-1);
        quicksort(array,pivot+1,right);
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
    quicksort(array, 0, MAXN);
    print(array);

    return 0;
}
