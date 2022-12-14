/*
47. Permutations II

Given a collection of numbers that might contain duplicates, return all possible unique permutations.



For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

/*
Difficulty:Medium
Total Accepted:126.2K
Total Submissions:385K

static int cmp_int(const void *ptr1, const void *ptr2)
{
    int a = *(int *)ptr1;
    int b = *(int *)ptr2;
    return (a > b) - (a < b);
}

static size_t factorial(size_t n)
{
    size_t result = 1;
    for (size_t i = 2; i <= n; ++i)
        result *= i;
    return result;
}

static inline void swap_int(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static bool next_permutation(int *arr, int arr_len)
{
    assert(arr || arr_len == 0);
    assert(arr_len >= 0);
    // from right to left, find first element smaller than its right neighbor
    int idx1 = arr_len - 2;
    for (; idx1 >= 0; --idx1)
        if (arr[idx1] < arr[idx1 + 1])
            break;
    // if not found the array is sorted in reverse, no more permutations
    if (idx1 < 0)
        return false;
    // from right to left, find first element greater than arr[idx1]
    int idx2 = arr_len - 1;
    for (; idx2 > idx1; --idx2)
        if (arr[idx2] > arr[idx1])
            break;
    // swap the two element and reverse the subarray starting at idx1 + 1
    swap_int(arr + idx1, arr + idx2);
    for (int i = idx1 + 1, j = arr_len - 1; i < j; ++i, --j)
        swap_int(arr + i, arr + j);
    return true;
}

/**
 * Return an array of arrays of size *out_result_len.
 * The sizes of the arrays are returned as *out_result_elem_lens array.
 * Note: Both returned array and *out_result_elem_lens array must be malloced,
 * assume caller calls free().
 */

int **
permuteUnique (
    int *nums, int nums_len,
    int *out_result_len, int **out_result_elem_lens)
{
    assert (nums || nums_len == 0);
    assert (nums_len >= 1);
    assert (out_result_len);
    assert (out_result_elem_lens);
    // the sorted array is the lexicographically smallest permutation
    // and we need it to calculate the result length
    qsort (nums, (size_t) nums_len, sizeof (*nums), cmp_int);
    // calculate result len
    size_t result_len = factorial ((size_t) nums_len);
    size_t count = 1;

    for (int i = 1; i < nums_len; ++i, ++count) {
        if (nums[i - 1] != nums[i]) {
            result_len /= factorial (count);
            count = 0;
        }
    }

    result_len /= factorial (count);
    // allocate memory
    int **result = malloc (result_len * sizeof (*result));

    if (!result)
    { return NULL; }

    int *result_elem_lens = malloc (result_len * sizeof (*result_elem_lens));

    if (!result_elem_lens) {
        free (result);
        return NULL;
    }

    for (size_t i = 0; i < result_len; ++i) {
        result[i] = malloc ((size_t) nums_len * sizeof (*result[i]));

        if (!result[i]) {
            for (size_t j = 0; j < i; ++j)
            { free (result[j]); }

            free (result_elem_lens);
            free (result);
            return NULL;
        }
    }

    // set output parameters
    for (size_t i = 0; i < result_len; ++i)
    { result_elem_lens[i] = nums_len; }

    *out_result_elem_lens = result_elem_lens;
    *out_result_len = (int) result_len;
    // copy each permutation to the result
    memcpy (result[0], nums, (size_t) nums_len * sizeof (*nums));

    for (size_t i = 1; i < result_len; ++i) {
        bool success = next_permutation (nums, nums_len);
        assert (success);
        memcpy (result[i], nums, (size_t) nums_len * sizeof (*nums));
    }

    return result;
}

/*
Companies LinkedIn Microsoft
Related Topics Backtracking
Similar Questions


                    Next Permutation

                    Permutations

                    Palindrome Permutation II
*/
