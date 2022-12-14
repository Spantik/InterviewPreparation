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
Fizz Buzz Implementation

Fizz Buzz is a very simple programming task, asked in software developer job interviews.

A typical round of Fizz Buzz can be:
Write a program that prints the numbers from 1 to 100 and for multiples of '3' print “Fizz”
instead of the number and for the multiples of '5' print “Buzz”.

1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, Fizz, 13, 14,
Fizz Buzz, 16, 17, Fizz, 19, Buzz, Fizz, 22, 23, Fizz, Buzz, 26,
Fizz, 28, 29, Fizz Buzz, 31, 32, Fizz, 34, Buzz, Fizz, ...
*/

int main ()
{
    for (int i = 1; i <100; i++){
        if (i % 3 == 0){
            if (i % 5 == 0){
                printf("Fizz Buzz, ");
            } else {
                printf("Fizz, ");
            }

        } else if (i % 5 == 0){
            printf("Buzz, ");
        } else {
            printf ("%d, ", i);
        }
    }
    printf("\r\n");

    return 0;
}
