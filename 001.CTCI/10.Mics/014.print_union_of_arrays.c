#include <stdio.h>

void print_union(int arr1[], size_t size1,  int arr2[], size_t size2)
{
	size_t i = 0;
	size_t j = 0;
	for (i = 0, j = 0; i < size1 && j < size2; )
	{
		if (arr1[i] < arr2[j])
		{
			printf("%d ", arr1[i]);
			i++;
		}
		else if (arr1[i] > arr2[j])
		{
			printf("%d ", arr2[j]);
			j++;
		}
		else
		{
			printf("%d ", arr1[i]);
			i++;
			j++;
		}
	}

	for (; i < size1 ; ) {
		printf("%d ", arr1[i]);
		i++;
	}

	for (; j < size2 ; ) {
		printf("%d ", arr2[j]);
		j++;
	}

	return;
}

int main()
{
	// Arrays must be sorted here
	int arr1[] = { 3, 4, 6, 9, 12, 15 };
	int arr2[] = { 4, 5, 7, 8, 9, 12 };
	size_t size1 = sizeof(arr1) / sizeof(*arr1);
	size_t size2 = sizeof(arr2) / sizeof(*arr2);

	printf("[3, 4, 6, 9, 12, 15] & [4, 5, 7, 8, 9, 12] \r\n");
	print_union(arr1, size1, arr2, size2);
	printf("\r\n");

	return 0;
}
