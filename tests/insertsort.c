#include "testheader.h"
#include "sort.h"
#define MUL 214013
#define ADD 2531011
int seed = 234;

void insertSort(int arr[],int len)
{
    int i,j;
    int key;
    for(i=1;i<len;i++)
    {
        key=arr[i];
        for(j=i-1;j>=0;j--)
        {
            if(arr[j]>key)
                arr[j+1]=arr[j];
            else 
                break;
        }
        arr[j+1]=key;
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
    insertSort(array, MAXN);
    #ifndef HIVEBOARD
    sys_state(0);
    print(array);
    #endif
    return 0;
}