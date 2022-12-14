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
    Given a sorted array of n uniformly distributed values arr[],
    write a function to search for a particular element x in the array.
    Linear Search finds the element in O(n) time, Jump Search takes O(√ n) time
    and Binary Search take O(Log n) time.

    The Interpolation Search is an improvement over Binary Search for instances,
    where the values in a sorted array are uniformly distributed.
    Binary Search always goes to the middle element to check. On the other hand,
    interpolation search may go to different locations according to the value of the
    key being searched. For example, if the value of the key is closer to the last element,
    interpolation search is likely to start search toward the end side.

    To find the position to be searched, it uses following formula.

    // The idea of formula is to return higher value of pos
    // when element to be searched is closer to arr[hi]. And
    // smaller value when closer to arr[lo]
    pos = lo + [ (x-arr[lo])*(hi-lo) / (arr[hi]-arr[Lo]) ]

    arr[] ==> Array where elements need to be searched
    x     ==> Element to be searched
    lo    ==> Starting index in arr[]
    hi    ==> Ending index in arr[]

    The formula for pos can be derived as follows.

    Let's assume that the elements of the array are linearly distributed.

    General equation of line : y = m*x + c.
    y is the value in the array and x is its index.

    Now putting value of lo,hi and x in the equation
    arr[hi] = m*hi+c ----(1)
    arr[lo] = m*lo+c ----(2)
    x = m*pos + c    ----(3)

    m = (arr[hi] - arr[lo] )/ (hi - lo)

    subtracting eqxn (2) from (3)
    x - arr[lo] = m * (pos - lo)
    lo + (x - arr[lo])/m = pos
    pos = lo + (x - arr[lo]) *(hi - lo)/(arr[hi] - arr[lo])

    Algorithm
    Rest of the Interpolation algorithm is the same except the above partition logic.
    Step1: In a loop, calculate the value of “pos” using the probe position formula.
    Step2: If it is a match, return the index of the item, and exit.
    Step3: If the item is less than arr[pos], calculate the probe position of the left sub-array.
           Otherwise calculate the same in the right sub-array.
    Step4: Repeat until a match is found or the sub-array reduces to zero.
*/


// If x is present in arr[0..n-1], then returns
// index of it, else returns -1.
int interpolationSearch(int arr[], int lo, int hi, int x)
{
    int pos;

    // Since array is sorted, an element present
    // in array must be in range defined by corner
    if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {

        // Probing the position with keeping
        // uniform distribution in mind.
        pos = lo + (((double)(hi - lo) / (arr[hi] - arr[lo])) * (x - arr[lo]));

        // Condition of target found
        if (arr[pos] == x)
            return pos;

        // If x is larger, x is in right sub array
        if (arr[pos] < x)
            return interpolationSearch(arr, pos + 1, hi, x);

        // If x is smaller, x is in left sub array
        if (arr[pos] > x)
            return interpolationSearch(arr, lo, pos - 1, x);
    }

    return -1;
}

// Driver Code
int main()
{
    // Array of items on which search will
    // be conducted.
    int arr[] = { 10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int x = 18; // Element to be searched
    int index = interpolationSearch(arr, 0, n - 1, x);

    // If element was found
    if (index != -1)
        printf("Element found at index %d\r\n", index);
    else
        printf("Element not found.\r\n");
    return 0;
}