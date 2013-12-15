#include "testheader.h"

#define MUL 214013
#define ADD 2531011
int seed = 234;

void heapsort(int[], int);
void heapify(int[], int);
void adjust(int[], int);

int main()
{
    int array[MAXN];
    int i;
    for (i = 0; i < MAXN; i++) {
        seed = seed * MUL + ADD;
        array[i] = seed;
    }
    sys_state(0);
    heapsort(array, MAXN);
    sys_state(0);
    sys_exit(0);
}

void heapsort(int array[], int n)
{
int i,t;

heapify(array,n);

for(i=n-1 ; i>0 ; i--)
{
t = array[0];
array[0] = array[i];
array[i] = t;
adjust(array,i);
}
}


void heapify(int array[], int n)
{
int item,i,j,k;

for(k=1 ; k<n ; k++)
{
item = array[k];
i = k;
j = (i-1)/2;

while( (i>0) && (item>array[j]) )
{
array[i] = array[j];
i = j;
j = (i-1)/2;
}
array[i] = item;
}
}

void adjust(int array[], int n)
{
int item,i,j;

j = 0;
item = array[j];
i = 2*j+1;

while(i<=n-1)
{
if(i+1 <= n-1)
if(array[i] < array[i+1])
i++;
if(item < array[i])
{
array[j] = array[i];
j = i;
i = 2*j+1;
}
else
	break;
}
array[j] = item;
}