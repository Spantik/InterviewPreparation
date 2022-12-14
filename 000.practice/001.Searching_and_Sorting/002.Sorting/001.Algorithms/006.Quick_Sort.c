#include "stdio.h"
#include "stdbool.h"
#include "limits.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "sys/types.h"
#include "assert.h"

// A utility functions
// maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }
// minimum of two integers
int min(int a, int b) { return (a < b) ? a : b; }

// Swap two integers
void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

/*
    Like Merge Sort, QuickSort is a Divide and Conquer algorithm.
    It picks an element as pivot and partitions the given array around the picked pivot.
    There are many different versions of quickSort that pick pivot in different ways.

    Always pick first element as pivot.
    Always pick last element as pivot (implemented below)
    Pick a random element as pivot.
    Pick median as pivot.

    The key process in quickSort is partition().
    Target of partitions is, given an array and an element x of array as pivot,
    put x at its correct position in sorted array and put all smaller elements (smaller than x) before x,
    and put all greater elements (greater than x) after x. All this should be done in linear time.

    Pseudo Code for recursive QuickSort function :

    // low  --> Starting index,  high  --> Ending index
    quickSort(arr[], low, high)
    {
        if (low < high)
        {
            // pi is partitioning index, arr[pi] is now at right place
            pi = partition(arr, low, high);

            quickSort(arr, low, pi - 1);  // Before pi
            quickSort(arr, pi + 1, high); // After pi
        }
    }

    Pseudo code for partition()

    This function takes last element as pivot, places the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right
    of pivot

    partition (arr[], low, high)
    {
        // pivot (Element to be placed at right position)
        pivot = arr[high];

        i = (low - 1)  // Index of smaller element and indicates the
                    // right position of pivot found so far

        for (j = low; j <= high- 1; j++)
        {
            // If current element is smaller than the pivot
            if (arr[j] < pivot)
            {
                i++;    // increment index of smaller element
                swap arr[i] and arr[j]
            }
        }
        swap arr[i + 1] and arr[high])
        return (i + 1)
    }
    Illustration of partition() :

    arr[] = {10, 80, 30, 90, 40, 50, 70}
    Indexes:  0   1   2   3   4   5   6

    low = 0, high =  6, pivot = arr[h] = 70
    Initialize index of smaller element, i = -1

    Traverse elements from j = low to high-1
    j = 0 : Since arr[j] <= pivot, do i++ and swap(arr[i], arr[j])
    i = 0
    arr[] = {10, 80, 30, 90, 40, 50, 70} // No change as i and j are same

    j = 1 : Since arr[j] > pivot, do nothing
    // No change in i and arr[]

    j = 2 : Since arr[j] <= pivot, do i++ and swap(arr[i], arr[j])
    i = 1
    arr[] = {10, 30, 80, 90, 40, 50, 70} // We swap 80 and 30

    j = 3 : Since arr[j] > pivot, do nothing
    // No change in i and arr[]

    j = 4 : Since arr[j] <= pivot, do i++ and swap(arr[i], arr[j])
    i = 2
    arr[] = {10, 30, 40, 90, 80, 50, 70} // 80 and 40 Swapped
    j = 5 : Since arr[j] <= pivot, do i++ and swap arr[i] with arr[j]
    i = 3
    arr[] = {10, 30, 40, 50, 80, 90, 70} // 90 and 50 Swapped

    We come out of loop because j is now equal to high-1.
    Finally we place pivot at correct position by swapping
    arr[i+1] and arr[high] (or pivot)
    arr[] = {10, 30, 40, 50, 70, 90, 80} // 80 and 70 Swapped

    Now 70 is at its correct place. All elements smaller than
    70 are before it and all elements greater than 70 are after
    it.
*/

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// A utility function to print a given array of given size
void printArray(int* arr, int size)
{
    int i;
    for (i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\r\n");
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


/* Driver program to test above functions */
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr)/sizeof(arr[0]);

    printf("\nUnSorted array is \n");
    printArray(arr, size);

    quickSort(arr, 0, size-1);

    printf("\nSorted array is \n");
    printArray(arr, size);
    return 0;
}
