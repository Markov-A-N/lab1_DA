#include "sort_lib.h"

int *Counting_Sort(int *a, int max_elem, int size, int *b)
{
	int c[max_elem + 1];
	for (int i = 0; i <= max_elem; i++)
	{
		c[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		++c[a[i]];
	}
	for (int i = 1; i <= max_elem; i++)
	{
		c[i] += c[i-1];
	}
	for (int i = size - 1; i >= 0; i--)
	{
		b[--c[a[i]]] = a[i];
	}

	return b;
}
//* * *  * * * * * * 
//0 5 4 12 1 5 3 8 4 7 0; size = 11
// 0  1  2  3  4  5  6  7  8  9  10  11  12
// 2  1  0  1  2  2  0  1  1  0   0   0   1
// 2  3  3  4  6  8  8  8 10 10  10  10  11 c
// 1  3  3  4  6  8  8  9 10 10  10  10  11 c_copy
//    0                    7