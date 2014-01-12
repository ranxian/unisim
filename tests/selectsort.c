#include "testheader.h"
#include "sort.h"
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
    #ifndef HIVEBOARD
    sys_state(0);
    #endif
    selectSort(array, MAXN);
    #ifndef HIVEBOARD
    sys_state(0);
    print(array);
    #endif
    return 0;
}