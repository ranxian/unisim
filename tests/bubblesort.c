#include "testheader.h"

#define MUL 214013
#define ADD 2531011
int seed = 234;

void bubbleSort(int arr[], int len)
{
    int i,j,temp;
    for(i=0;i<len;i++)
    {
        for(j=0;j<len-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
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
    bubbleSort(array, MAXN);
    sys_state(0);
    sys_exit(0);
    // print(array);
    return 0;
}