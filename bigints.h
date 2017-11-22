#include <stdio.h>
#include <string.h>
#define MAX_DIGITS 1000

struct bigint {
    int length;
    int digits[MAX_DIGITS];
};
typedef struct bigint bigint;

bigint create_bigint_from_string(char *string);
bigint bigint_add(bigint a, bigint b);
bigint bigint_subtract(bigint a, bigint b);
bigint bigint_multiply(bigint a, bigint b);
bigint bigint_divide(bigint a, bigint b);
bigint bigint_modulus(bigint a, bigint b);
int bigint_compare(bigint a, bigint b);
int bigint_compare_helper(bigint a, bigint b, int length);
int custom_pow(int a, int b);
int char_to_int(char c);
