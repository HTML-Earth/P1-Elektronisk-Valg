#include "bigints.h"

/*
int main(void) {
    int i;
    bigint a, b, result;

    a = create_bigint_from_string("1100");
    b = create_bigint_from_string("1");

    result = bigint_subtract(a, b);

    for (i = result.length - 1; i >= 0; i--) {
        printf("%d", result.digits[i]);
    }

    printf("\n");

    return 0;
}
*/

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
    int i, length, added;
	int mente=0;

    result = create_bigint_from_string("0");

    length = (a.length > b.length) ? a.length : b.length;

    for (i = 0; i < length; i++) {
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
    int i, length, subbed, mente = 0, borrow;

    result = create_bigint_from_string("0");

    length = (a.length > b.length) ? a.length : b.length;

    for (i = 0; i < length; i++) {
        borrow = (a.digits[i] < b.digits[i] || a.digits[i] < mente) ? 10 : 0;
        subbed = a.digits[i] - b.digits[i] + borrow - mente;

        mente = (a.digits[i] < b.digits[i] || a.digits[i] < mente) ? 1 : 0;

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
    bigint result, temp;
    int i, j, k, tempint;
    char str[MAX_DIGITS];
    result = create_bigint_from_string("0");

    for (i = 0; i < a.length; i++) {
        for (j = 0; j < b.length; j++) {
            tempint = a.digits[i] * b.digits[j];
            sprintf(str, "%d", tempint);

            for (k = 0; k < i + j; k++)
                strcat(str, "0");

            temp = create_bigint_from_string(str);
            result = bigint_add(result, temp);
        }
    }

    return result;
}

/* UNOPTIMIZED Multiplies two bigints */
bigint bigint_multiply_old(bigint a, bigint b) {
    int i, j;
    bigint result;
    result = create_bigint_from_string("0");

    for (i = 0; i < b.length; i++) {
        for (j = 0; j < custom_pow(10, i) * b.digits[i]; j++) {
            result = bigint_add(result, a);
        }
    }

    return result;
}

/* Divides two bigints */
bigint bigint_divide(bigint a, bigint b) {
    bigint result, times, one;

    result = create_bigint_from_string("0");
    times = create_bigint_from_string("0");
    one = create_bigint_from_string("1");

    while (bigint_compare(result, a) < 0) {
        result = bigint_add(result, b);
        times = bigint_add(times, one);
    }

    if (bigint_compare(result, a) > 0)
        times = bigint_subtract(times, one);

    return times;
}

/* a % b */
bigint bigint_modulus(bigint a, bigint b) {
    bigint result;

    result = create_bigint_from_string("0");

    while (bigint_compare(result, a) < 0) {
        result = bigint_add(result, b);
    }

    if (bigint_compare(result, a) > 0)
        result = bigint_subtract(result, b);

    result = bigint_subtract(a, result);

    return result;
}

/* Bigint power function */
bigint bigint_pow(bigint a, bigint b)
{
    bigint result, i, one;

    result = create_bigint_from_string("1");
    i = create_bigint_from_string("0");
    one = create_bigint_from_string("1");

    while (bigint_compare(i, b) < 0) {
        result = bigint_multiply(result, a);
        i = bigint_add(i, one);
    }

    return result;
}

/* Returns 1 if a is bigger, -1 if b is bigger, or 0 if they are equal */
int bigint_compare(bigint a, bigint b) {
    if (a.length > b.length)
        return 1;
    else if (a.length < b.length)
        return -1;
    else
        return bigint_compare_helper(a, b, a.length);
}

/* Recursive function used by bigint_compare */
int bigint_compare_helper(bigint a, bigint b, int length) {
    if (a.digits[length-1] > b.digits[length-1])
        return 1;
    else if (a.digits[length-1] < b.digits[length-1])
        return -1;
    else {
        if (length < 2)
            return 0;
        else
            return bigint_compare_helper(a, b, length-1);
    }
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

/* Power function that works with ints */
int custom_pow(int a, int b)
{
    int res = 1, i;
    for (i = 0; i < b; i++)
        res *= a;

    return res;
}
