#include "stdio.h"
#include "stdbool.h"
#include "limits.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "sys/types.h"
#include "assert.h"

int
numOfPairs (char **nums, int numsSize, char *target)
{
    int i, j, ans;
    int size_1, size_2, size_target;
    char *temp;
    ans = 0;
    size_target = strlen (target);
    temp = (char *)malloc (sizeof (char) * (size_target + 1));
    memset (temp, 0x0, sizeof (char) * (size_target + 1));

    for (i = 0; i < numsSize; i++) {
        size_1 = strlen (nums[i]);

        for (j = i + 1; j < numsSize; j++) {
            size_2 = strlen (nums[j]);

            if ((size_1 + size_2) != size_target) {
                continue;
            }

            /* str1 + str2 */
            strncpy (temp, nums[i], size_1);
            strncpy (temp + size_1, nums[j], size_2);
            temp[size_target] = '\0';

            if (!strcmp (temp, target)) {
                ans++;
            }

            /* str2 + str1 */
            strncpy (temp, nums[j], size_2);
            strncpy (temp + size_2, nums[i], size_1);
            temp[size_target] = '\0';

            if (!strcmp (temp, target)) {
                ans++;
            }
        }
    }

    return ans;
}