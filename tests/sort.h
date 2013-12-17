#ifndef SORT_H
#define SORT_H
#include "testheader.h"
void print(int arr[])
{
	int i;
	for (i = 0; i < MAXN; i++)
	{
		sys_putint(arr[i]);
	}
}
#endif