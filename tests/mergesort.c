#include "testheader.h"

#define MUL 214013
#define ADD 2531011
int seed = 234;

void merge(int arr[],int p,int q,int r)
{
    int A[MAXN],B[MAXN];
    int n1,n2,i,j,k;
    n1=q-p+1;
    n2=r-q;

    for(i=0;i<n1;i++)
    {
        A[i]=arr[p+i];
    }
    A[i]=1e8;
    for(i=0;i<n2;i++)
    {
        B[i]=arr[q+i+1];
    }
    B[i]=1e8;
    i=0;j=0;
    for(k=p;k<=r;k++)
    {
        if(A[i]>B[j])
        {
            arr[k]=B[j];
            j++;
        }else{
            arr[k]=A[i];
            i++;
        }
    }
}

void mergeSort(int arr[],int begin,int end)
{
    int mid;
    if(begin<end)
    {
        mid=(begin+end)/2;
        mergeSort(arr,begin,mid);
        mergeSort(arr,mid+1,end);
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
    sys_exit(0);
    // print(array);
    return 0;
}