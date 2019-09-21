#include <iostream>
#include <cstdlib>
#include "sort_lib.h"

#define SIZE 5

int main(int argc, char *argv[])
{
	int *a = new int [SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		std::cin >> a[i];
	}

	int *m = new int [sizeof(a) / sizeof(int)], *l;
	l = Counting_Sort(a, 69, SIZE, m);

	delete[] a;

	a = l;

	for (int i = 0; i < SIZE; i++)
	{
		std::cout << l[i] << " ";
	}

	std::cout << "\n" << sizeof(int *) << "\n";


	return 0;
}