#include <stdio.h>
#include <string.h>
#include <math.h>

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

int char_to_int(char c);

int main(void) {
    int i;
    bigint a, b, result;

    a = create_bigint_from_string("4");
    b = create_bigint_from_string("5");

    result = bigint_multiply(a, b);

    for (i = result.length - 1; i >= 0; i--) {
        printf("%d", result.digits[i]);
    }

    printf("\n");

    return 0;
}

/* Creates a bigint from a string */
bigint create_bigint_from_string(char *string) {
    bigint b;
    int i;
    b.length = strlen(string);

    for (i = 0; i < MAX_DIGITS; i++) {
        b.digits[i] = 0;
    }

    for (i = b.length - 1; i >= 0; i--) {
        b.digits[i] = char_to_int(string[b.length - 1 - i]);
    }

    return b;
}

/* Adds two bigints */
bigint bigint_add(bigint a, bigint b) {
    bigint result;
    int i, length, added, mente;

    result = create_bigint_from_string("0");

    length = (a.length > b.length) ? a.length : b.length;

    for (i = 0; i < length; i++){
        added = a.digits[i] + b.digits[i] + mente;

        if (added > 9) {
            result.digits[i] = added - 10;
            mente = 1;
            if (i == length - 1)
                length++;
        }
        else {
            result.digits[i] = added;
            mente = 0;
        }
    }
    result.length = length;

    return result;
}

/* Subtracts two bigints (only works for a >= b) */
bigint bigint_subtract(bigint a, bigint b) {
    bigint result;
    int i, length, subbed, mente, borrow;

    result = create_bigint_from_string("0");

    length = (a.length > b.length) ? a.length : b.length;

    for (i = 0; i < length; i++){
        borrow = (a.digits[i] < b.digits[i]) ? 10 : 0;
        subbed = a.digits[i] - b.digits[i] + borrow - mente;

        mente = (a.digits[i] < b.digits[i]) ? 1 : 0;

        result.digits[i] = (subbed < 0) ? 0 : subbed;
    }
    i = length - 1;
    while (i > 0 && result.digits[i] == 0) {
        length--;
        i--;
    }
    result.length = length;

    return result;
}

/* Multiplies two bigints */
bigint bigint_multiply(bigint a, bigint b) {
    int i, j;
    bigint result;
    result = create_bigint_from_string("0");

    for (i = 0; i < b.length; i++) {
        for (j = 0; j < pow(10, i) * b.digits[i]; j++) {
            result = bigint_add(result, a);
        }
    }

    return result;
}

/* Divides two bigints */
bigint bigint_divide(bigint a, bigint b) {
    bigint result;
    return result;
}

/* a % b */
bigint bigint_modulus(bigint a, bigint b) {
    bigint result;
    return result;
}

/* Converts char to int */
int char_to_int(char c) {
    switch (c) {
        case '0':
        return 0;
        case '1':
        return 1;
        case '2':
        return 2;
        case '3':
        return 3;
        case '4':
        return 4;
        case '5':
        return 5;
        case '6':
        return 6;
        case '7':
        return 7;
        case '8':
        return 8;
        case '9':
        return 9;
    }
    return -1;
}
