#include "stdio.h"
#include "stdbool.h"
#include "limits.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "sys/types.h"
#include "assert.h"
#include "time.h"

#define SWAP(a_m, b_m)  (((a_m) ^= (b_m)), ((b_m) ^= (a_m)), ((a_m) ^= (b_m)))
#define MIN(a_m,b_m)    (b_m ^ ((a_m ^ b_m) & -(a_m < b_m)))
#define MAX(a_m,b_m)    (a_m ^ ((a_m ^ b_m) & -(a_m < b_m)))
#define SETBIT(flag_m, mask_m, val_m) (val_m = (val_m & ~mask_m) | (-flag_m & mask_m))
#define MERGE(a_m,b_m,r_m,mask_m) (r_m = a_m ^ ((a_m ^ b_m) & mask_m))

// Print a digit in binary
void dumpBinary(int n, char reason[]) {
    int i;
    printf("0");
    for (i = 1 << 30; i > 0; i = i / 2) {
        if((n & i) != 0) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("[ %d ]: %s ", n, reason);
    printf("\r\n");
}

/* Size of array 64 K */
#define SIZE (1 << 16)

/* Meta program that generates set bit count array of first 256 integers */

/* GROUP_A - When combined with META_LOOK_UP generates count for 4x4 elements */
#define GROUP_A(x) x, x + 1, x + 1, x + 2

/* GROUP_B - When combined with META_LOOK_UP generates count for 4x4x4 elements */
#define GROUP_B(x) GROUP_A(x), GROUP_A(x+1), GROUP_A(x+1), GROUP_A(x+2)

/* GROUP_C - When combined with META_LOOK_UP generates count for 4x4x4x4 elements */
#define GROUP_C(x) GROUP_B(x), GROUP_B(x+1), GROUP_B(x+1), GROUP_B(x+2)

/* Provide appropriate letter to generate the table */
#define META_LOOK_UP(PARAMETER) \
   GROUP_##PARAMETER(0),  \
   GROUP_##PARAMETER(1),  \
   GROUP_##PARAMETER(1),  \
   GROUP_##PARAMETER(2)   \

int countSetBits(int array[], size_t array_size)
{
   int count = 0;

   /* META_LOOK_UP(C) - generates a table of 256 integers whose
      sequence will be number of bits in i-th position
      where 0 <= i < 256
   */

    /* A static table will be much faster to access */
       static unsigned char const look_up[] = { META_LOOK_UP(C) };

    /* No shifting funds (for better readability) */
    unsigned char *pData = NULL;

    for(size_t index = 0; index < array_size; index++)
    {
        /* It is fine, bypass the type system */
        pData = (unsigned char *)&array[index];

        /* Count set bits in individual bytes */
        count += look_up[pData[0]];
        count += look_up[pData[1]];
        count += look_up[pData[2]];
        count += look_up[pData[3]];
    }

   return count;
}

/* Driver program, generates table of random 64 K numbers */
int main()
{
   int index;
   int random[SIZE];

   /* Seed to the random-number generator */
   srand((unsigned)time(0));

   /* Generate random numbers. */
   for( index = 0; index < SIZE; index++ ) {
      random[index] = rand();
   }

   printf("Total number of bits = %d\n", countSetBits(random, SIZE));
   return 0;
}