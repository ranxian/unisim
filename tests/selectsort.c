#include "testheader.h"

#define MUL 214013
#define ADD 2531011
int seed = 234;

void selectSort(int arr[],int len)
{
    int i,j,temp;
    for(i=0;i<len;i++)
    {
        for(j=i+1;j<len;j++)
        {
            if(arr[i]>arr[j])
            {
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
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
    selectSort(array, MAXN);
    sys_state(0);
    sys_exit(0);
    // print(array);
    return 0;
}