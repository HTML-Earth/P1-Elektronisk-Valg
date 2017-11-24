#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_DIGITS 1000

struct bigint {
    int length;
    int *digits;
};
typedef struct bigint bigint;

/* Creates a bigint from a string */
bigint create_bigint_from_string(char *string);

/* Prints bigint to standard output */
void bigint_print(bigint b);

/* Prints bigint to a string */
void bigint_print_string(char *str, bigint b);

/* Prints bigint to a file */
void bigint_print_file(FILE *file, bigint b);

/* Adds two bigints */
bigint bigint_add(bigint a, bigint b);

/* Subtracts two bigints (only works for a >= b) */
bigint bigint_subtract(bigint a, bigint b);

/* Multiplies two bigints */
bigint bigint_multiply(bigint a, bigint b);

/* Divides two bigints */
bigint bigint_divide(bigint a, bigint b);

/* a % b */
bigint bigint_modulus(bigint a, bigint b);

/* Bigint power function */
bigint bigint_pow(bigint a, bigint b);

/* Returns 1 if a is bigger, -1 if b is bigger, or 0 if they are equal */
int bigint_compare(bigint a, bigint b);

/* Recursive function used by bigint_compare */
int bigint_compare_helper(bigint a, bigint b, int length);

/* Converts char to int */
int char_to_int(char c);

/* Power function that works with ints */
int custom_pow(int a, int b);
