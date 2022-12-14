#include "stdio.h"
#include "stdbool.h"
#include "limits.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
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
    The name of this searching algorithm may be misleading as it works in O(Log n) time.
    The name comes from the way it searches an element.

    Given a sorted array, and an element x to be searched, find position of x in the array.

    Input:  arr[] = {10, 20, 40, 45, 55}
            x = 45
    Output: Element found at index 3

    Input:  arr[] = {10, 15, 25, 45, 55}
            x = 15
    Output: Element found at index 1

    Exponential search involves two steps:
        1. Find range where element is present
        2. Do Binary Search in above found range.

    How to find the range where element may be present?
    The idea is to start with subarray size 1, compare its last element with x, then try size 2,
    then 4 and so on until last element of a subarray is not greater.

    Once we find an index i (after repeated doubling of i),
    we know that the element must be present between i/2 and i
    (Why i/2? because we could not find a greater value in previous iteration)
*/


// A recursive binary search function. It returns
// location of x in  given array arr[l..r] is
// present, otherwise -1
int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l)/2;

        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;

        // If element is smaller than mid, then it
        // can only be present n left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid-1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid+1, r, x);
    }

    // We reach here when element is not present
    // in array
    return -1;
}

// Returns position of first occurrence of
// x in array
int exponentialSearch(int arr[], int n, int x)
{
    // If x is present at first location itself
    if (arr[0] == x)
        return 0;

    // Find range for binary search by repeated doubling
    int i = 1;
    while (i < n && arr[i] <= x) {
        i = i*2;
    }

    //  Call binary search for the found range.
    return binarySearch(arr, i/2, min(i, n-1), x);
}

// Driver code
int main(void)
{
   int arr[] = {2, 3, 4, 10, 40};
   int n = sizeof(arr)/ sizeof(arr[0]);
   int x = 10;

   int result = exponentialSearch(arr, n, x);
   (result == -1)? printf("Element is not present in array\r\n")
                 : printf("Element is present at index %d\r\n", result);
   return 0;
}