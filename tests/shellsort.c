#include "testheader.h"
#define MUL 214013
#define ADD 2531011
int seed = 234;

void shellsort(int array[], int n)
{
    int i, j, temp; 
    int gap = 0;

    while (gap<=n)
    {
        gap = gap * 3 + 1;
    } 
    while (gap > 0) 
    {
        for ( i = gap; i < n; i++ )
        {
            j = i - gap;
            temp = array[i];             
            while (( j >= 0 ) && ( array[j] > temp ))
            {
                array[j + gap] = array[j];
                j = j - gap;
            }
            array[j + gap] = temp;
        }
        gap = ( gap - 1 ) / 3;
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
    shellsort(array, MAXN);
    sys_state(0);
    sys_exit(0);
    // print(array);
    return 0;
}