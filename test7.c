// qsort test
#ifndef X86
#include "stdlib.h"
#endif

#ifdef X86
    #include <stdio.h>
    void sys_putint(int i) {
        printf("%d\n", i);
    }
#endif

void print(int *array)
{
    int i;
    for (i = 0; i < 3; i++) {
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
    print(array);
    sys_putint(left);
    sys_putint(right);
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
        sys_putint(i);
    sys_putint(1111111111);

    return i;
}

void quicksort(int array[], int left, int right)
{
    //Do nothing if left <= right

    sys_putint(left);
    sys_putint(right);
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
    int array[] = { 3, 1, 2 };
    quicksort(array, 0, 3);
    print(array);
}