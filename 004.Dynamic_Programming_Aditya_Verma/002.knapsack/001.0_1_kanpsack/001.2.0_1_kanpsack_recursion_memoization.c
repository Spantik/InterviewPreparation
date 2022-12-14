#include "stdio.h"
#include "stdbool.h"
#include "limits.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "sys/types.h"
#include "assert.h"

/*
    Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum
    total value in the knapsack. In other words, given two integer arrays val[0..n-1] and wt[0..n-1]
    which represent values and weights associated with n items respectively. Also given an integer W
    which represents knapsack capacity, find out the maximum value subset of val[] such that sum of the
    weights of this subset is smaller than or equal to W. You cannot break an item, either pick the complete
    item or don’t pick it (0-1 property).
*/

int Memoization[102][1002];

// A utility function that returns
// maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Returns the maximum value that can be
// put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
    // Base Case
    if (n == 0 || W == 0)
        return 0;

    if (Memoization[n][W] != -1) {
        return Memoization[n][W];
    }

    // If weight of the nth item is more than Knapsack capacity W,
    // then this item cannot be included in the optimal solution
    if (wt[n - 1] > W)
        Memoization[n][W] = knapSack(W, wt, val, n - 1);

    // Return the maximum of two cases:
    // (1) nth item included
    // (2) not included
    else
        Memoization[n][W] = max((val[n - 1] + knapSack(W - wt[n - 1], wt, val, n - 1)), (knapSack(W, wt, val, n - 1)));

    return Memoization[n][W];
}

// Driver program to test above function
int main()
{
    int val[] = { 60, 100, 120 };
    int wt[] = { 10, 20, 30 };
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    printf("Value Array [ 60, 100, 120 ] \r\n");
    printf("Weight Array [ 10, 20, 30 ] \r\n");
    printf("Knapsack Capacity 50 \r\n");

    memset(Memoization, -1, sizeof(Memoization));
    printf("The maximum total value in the knapsack %d \r\n", knapSack(W, wt, val, n));
    return 0;
}