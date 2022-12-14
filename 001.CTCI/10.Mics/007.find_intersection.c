#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "limits.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "sys/types.h"
#include "assert.h"

// Code to find the intersection of the sorted arrays

void print_intersection(int arr1[], size_t size1,  int arr2[], size_t size2)
{
	for (size_t i = 0, j = 0; i < size1 && j < size2; )
	{
		if (arr1[i] < arr2[j])
			i++;
		else if (arr1[i] > arr2[j])
			j++;
		else
		{
			printf("%d ", arr1[i]);
			i++;
			j++;
		}
	}
}

int main()
{
	// Arrays must be sorted here
	int arr1[] = { 3, 4, 6, 9, 12, 15 };
	int arr2[] = { 4, 5, 7, 8, 9, 12 };
	size_t size1 = sizeof(arr1) / sizeof(*arr1);
	size_t size2 = sizeof(arr2) / sizeof(*arr2);

	printf ("Two Array [3, 4, 6, 9, 12, 15] & [4, 5, 7, 8, 9, 12] \r\n\t Intersection: ");
	print_intersection(arr1, size1, arr2, size2);
	printf ("\r\n");

	return 0;
}
