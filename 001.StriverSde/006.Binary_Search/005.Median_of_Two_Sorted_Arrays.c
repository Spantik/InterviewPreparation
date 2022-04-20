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
    Median of Two Sorted Arrays of different sizes
    Problem Statement: Given two sorted arrays arr1 and arr2 of size m and n respectively,
    return the median of the two sorted arrays.

    Example 1:
    Input format: arr1 = [1,4,7,10,12], arr2 = [2,3,6,15]
    Output format : 6.00000
    Explanation:
        Merge both arrays. Final sorted array is [1,2,3,4,6,7,10,12,15].
        We know that to find the median we find the mid element. Since, the size of the element is odd.
        By formula, the median will be at [(n+1)/2]th position of the final sorted array.
        Thus, for this example, the median is at [(9+1)/2]th position which is [5]th = 6.

    Example 2:
    Input: arr1 = [1], arr2 = [2]
    Output format:
    1.50000
    Explanation:
    Merge both arrays. Final sorted array is [1,2].
    We know that to find the median we find the mid element.
    Since, the size of the element is even.
    By formula, the median will be the mean of elements at [n/2]th and  [(n/2)+1]th position of
    the final sorted array. Thus, for this example, the median is (1+2)/2 = 3/2 = 1.50000.
*/

#define MAX(a_, b_) (a_ > b_ ? a_ : b_)
#define MIN(a_, b_) (a_ < b_ ? a_ : b_)

float median(int nums1[], int nums2[], int m, int n)
{
    int finalArray[n+m];
    int i = 0,j = 0,k = 0;

    while(i < m && j < n) {
        if(nums1[i] < nums2[j]) {
            finalArray[k++] = nums1[i++];
        } else {
            finalArray[k++] = nums2[j++];
        }
    }

    if(i<m) {
        while(i<m)
            finalArray[k++] = nums1[i++];
    }

    if(j<n) {
        while(j<n)
            finalArray[k++] = nums2[j++];
    }

    n = n + m;
    if(n%2 == 1) {
        return finalArray[((n+1)/2)-1];
    } else {
        return ((float)finalArray[(n/2)-1] + (float)finalArray[(n/2)])  / 2;
    }
}

float medianBinary (int nums1[], int nums2[], int m, int n)
{
    //Ensuring that binary search happens on minimum size array
    if(m > n) {
        return medianBinary(nums2, nums1, n, m);
    }

    int low = 0;
    int high = m;
    int medianPos = ((m+n)+1) / 2;

    while(low <= high) {
        int cut1 = (low+high) >> 1;
        int cut2 = medianPos - cut1;

        int l1 = (cut1 == 0) ? INT_MIN : nums1[cut1-1];
        int l2 = (cut2 == 0) ? INT_MIN : nums2[cut2-1];
        int r1 = (cut1 == m) ? INT_MAX : nums1[cut1];
        int r2 = (cut2 == n) ? INT_MAX : nums2[cut2];

        if(l1 <= r2 && l2 <= r1) {
            if((m+n)%2 != 0) {
                return MAX(l1,l2);
            } else {
                return (MAX(l1,l2) + MIN(r1,r2)) / 2.0;
            }
        } else if(l1 > r2) {
            high = cut1 - 1;
        } else {
            low = cut1 + 1;
        }
    }
    return 0.0;
}

float medianBinaryEfficient (int nums1[], int nums2[], int m, int n)
{
    //ensuring that binary search happens on minimum size array
    if(m > n ) {
        return median(nums2,nums1,n,m);
    }

    int low=0;
    int high=m;
    int medianPos = ((m+n)+1) / 2;

    while(low <= high) {

        int cut1 = (low + high) >>1;
        int cut2 = medianPos - cut1;

        int l1 = (cut1 == 0)? INT_MIN : nums1[cut1-1];
        int l2 = (cut2 == 0)? INT_MIN : nums2[cut2-1];

        int r1 = (cut1 == m) ? INT_MAX : nums1[cut1];
        int r2 = (cut2 == n) ? INT_MAX : nums2[cut2];

        if(l1 <= r2 && l2 <= r1) {

            if((m+n) %2 != 0) {

                return MAX(l1,l2);
            } else {

                return (MAX(l1,l2) + MIN(r1,r2)) / 2.0;
            }
        } else if(l1 > r2) {

            high = cut1-1;
        } else {

            low = cut1+1;
        }
    }

    return 0.0;
}

int main() {

    int nums1[] = {1,4,7,10,12};
    int nums2[] = {2,3,6,15};

    int m = sizeof(nums1)/sizeof(nums1[0]);
    int n = sizeof(nums2)/sizeof(nums2[0]);

    printf("[Naive Approach] The median of two sorted array is %f \r\n",median(nums1,nums2,m,n));
    printf("[Binary Search Approach] The median of two sorted array is %f \r\n",medianBinary(nums1,nums2,m,n));
    printf("[Binary Search Efficient Approach] The median of two sorted array is %f \r\n",medianBinaryEfficient(nums1,nums2,m,n));
    return 0;
}