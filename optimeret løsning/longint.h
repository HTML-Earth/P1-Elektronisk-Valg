#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#define MAX_CHARS 50000
#define MAX_DIGITS 50000

typedef struct{
  long base;
  int lenght;
  int max_digits;
  uint16_t *digit;
} longint;

typedef struct {
    int base;
    int length;
    int max_digits;
    uint8_t *digits;
} bigint;

longint *create_longint (int base, int length);

longint *create_longint_from_string(char *str);

longint* create_base10_from_string(int base, char *string);

longint *longint_add(longint *a, longint *b);

void longint_clear (longint **b);

void longint_print(longint *l);

void longint_print_string(char *str, longint *l);

longint *convert_base10_to_longint(char *str);

longint *longint_subtract(longint *a, longint *b);

int longint_compare(longint *a, longint *b);

int longint_compare_helper(longint *a, longint *b, int max_digits);

longint *longint_karasuba(longint *l1, longint *l2);

longint *longint_multiply(longint *a, longint *b);

longint *longint_divide(longint *a, longint *b);

longint *longint_modulus(longint *a, longint *b);

longint *direct_longint_from_string(char *string);

bigint *create_bigint_copy_from_longint(longint *b);

bigint *convert_longint_to_bigint(longint *l);

uint16_t conversion_value(longint *b);

int longint_even(longint *l);

int odd(long double pow);

long double power(long double number, long double pow);

long double sqr(long double pow);

longint *recursive_divrem(longint *a, longint *b, longint *rem);

longint *longint_power(longint *a, longint *b);

longint *recursive_binary_conversion(longint *l);

longint *recursive_radix_conversion(longint *l);

/* Converts char to int */
int char_to_int(char c);
