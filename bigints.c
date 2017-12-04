#include "bigints.h"

/* Creates an empty bigint with defined length */
bigint *create_bigint (int length) {
    bigint *b = (bigint *)calloc(1, sizeof(bigint));
    b->length = 1;
    b->max_digits = length;
    b->digits = (int*)calloc(length, sizeof(int));
    return b;
}

/* Creates a bigint from a string */
bigint *create_bigint_from_string(char *string) {
    bigint *b;
    int i, ph, j = 0;

    b = create_bigint(strlen(string));
    b->length = b->max_digits;

    for (i = b->max_digits - 1; i >= 0; i--) {
       ph = char_to_int(string[j]);
       b->digits[i] = ph;
       j++;
    }

    return b;
}

/* frees up a bigint's allocated memory */
void bigint_clear (bigint *b) {
    free(b->digits);
    free(b);
}

/* Prints bigint to standard output */
void bigint_print(bigint *b) {
    int i;
    for (i = b->length - 1; i >= 0; i--) {
        printf("%d", b->digits[i]);
    }
}

/* Prints bigint to a string */
void bigint_print_string(char *str, bigint *b) {
    int i, j = 0;
    for (i = b->length - 1; i >= 0; i--) {
        sprintf(str+j, "%d", b->digits[i]);
        j++;
    }
}

/* Prints bigint to a file */
void bigint_print_file(FILE *file, bigint *b) {
    int i;
    for (i = b->length - 1; i >= 0; i--) {
        fprintf(file, "%d", b->digits[i]);
    }
}

/* Adds two bigints */
bigint *bigint_add(bigint *a, bigint *b) {
    bigint *result;
    int i, length, added, temp_a, temp_b;
	int mente = 0;

    length = (a->length > b->length) ? a->length : b->length;

    result = create_bigint(length+1);

    for (i = 0; i < length; i++) {
        temp_a = (i < a->length) ? a->digits[i] : 0;
        temp_b = (i < b->length) ? b->digits[i] : 0;
        added = temp_a + temp_b + mente;

        if (added > 9) {
            result->digits[i] = added - 10;
            mente = 1;
            if (i == length-1)
                length++;
        }
        else {
            result->digits[i] = added;
            mente = 0;
        }
    }
    result->length = length;

    return result;
}

/* Subtracts two bigints (only works for a >= b) */
bigint *bigint_subtract(bigint *a, bigint *b) {
    bigint *result;
    int i, length, subbed, mente = 0, borrow, temp_a, temp_b;

    /* result length is length of longest parameter */
    length = (a->length > b->length) ? a->length : b->length;

    /* create result variable */
    result = create_bigint(length);

    for (i = 0; i < length; i++) {
        /* use zero if i over length */
        temp_a = (i < a->length) ? a->digits[i] : 0;
        temp_b = (i < b->length) ? b->digits[i] : 0;

        borrow = (temp_a < temp_b || temp_a < mente) ? 10 : 0;
        subbed = temp_a - temp_b + borrow - mente;
        mente = (temp_a < temp_b || temp_a < mente) ? 1 : 0;

        if (subbed < 0) {
            subbed += 10;
            mente = 1;
        }

        result->digits[i] = (subbed < 0) ? 0 : subbed;
    }

    i = length-1;

    while (i > 0 && result->digits[i] == 0) {
        length--;
        i--;
    }

    result->length = length;

    return result;
}

/* Multiplies two bigints */
bigint *bigint_multiply(bigint *a, bigint *b) {
    bigint *result, *previous, *temp;
    int ia, ib, zeroes, tempint;
    char *str;

    str = (char *)calloc(a->length + b->length, sizeof(char));

    /* result max digits is combined digit amount */
    result = create_bigint(a->length + b->length);

    if ((a->length == 1 && a->digits[0] == 0) || (b->length == 1 && b->digits[0] == 0)){
        /* multiplication by 0, therefore the result is 0 */
        free(str);
        return result;
    }

    previous = result;

    /* for each digit pair */
    for (ia = 0; ia < a->length; ia++) {
        for (ib = 0; ib < b->length; ib++) {
            /* multiply ints */
            tempint = a->digits[ia] * b->digits[ib];

            /* add result to string */
            sprintf(str, "%d", tempint);

            /* add zeroes to end of string */
            for (zeroes = 0; zeroes < ia + ib; zeroes++)
                strcat(str, "0");

            /* make bigint from string, and add to overall result */
            temp = create_bigint_from_string(str);

            result = bigint_add(result, temp);

            bigint_clear(temp);

            bigint_clear(previous);
            previous = result;
        }
    }

    free(str);
    bigint_clear(temp);

    return result;
}

/* UNOPTIMIZED Multiplies two bigints */
bigint *bigint_multiply_old(bigint *a, bigint *b) {
    int i, j;
    bigint *result;
    result = create_bigint_from_string("0");

    for (i = 0; i < b->length; i++) {
        for (j = 0; j < custom_pow(10, i) * b->digits[i]; j++) {
            result = bigint_add(result, a);
        }
    }

    return result;
}

/* Divides two bigints */
bigint *bigint_divide(bigint *a, bigint *b) {
    bigint *sum, *times, *one;
    int sum_length;

    sum_length = (a->length > b->length) ? a->length : b->length;

    sum = create_bigint(sum_length+1);
    times = create_bigint(a->length);
    one = create_bigint_from_string("1");

    while (bigint_compare(sum, a) < 0) {
        sum = bigint_add(sum, b);
        times = bigint_add(times, one);
    }

    if (bigint_compare(sum, a) > 0)
        times = bigint_subtract(times, one);

    bigint_clear(sum);
    bigint_clear(one);

    return times;
}

/* a % b */
bigint *bigint_modulus(bigint *a, bigint *b) {
    bigint *result, *subtractor;
    char b_str[MAX_DIGITS];
    int i, zeroes;

    if (a->length < b->length)
        return a;
    else if (a->length == b->length && bigint_compare(a,b) == -1){
        return a;
    }
    else {
        result = a;

        do {
            memset(b_str, '\0', MAX_DIGITS);
            bigint_print_string(b_str, b);

            if (result->length > b->length + 1) {
                zeroes = result->length - b->length - 1;

                for (i = 0; i < zeroes; i++)
                    strcat(b_str, "0");
            }

            subtractor = create_bigint_from_string(b_str);
            result = bigint_subtract(result, subtractor);
        }
        while (bigint_compare(result, b) >= 0);

        bigint_clear(subtractor);

        return result;
    }
}

/* UNOPTIMIZED a % b */
bigint *bigint_modulus_old(bigint *a, bigint *b) {
    bigint *result;

    result = create_bigint(b->length);

    while (bigint_compare(result, a) < 0) {
        result = bigint_add(result, b);
    }

    if (bigint_compare(result, a) > 0)
        result = bigint_subtract(result, b);

    result = bigint_subtract(a, result);

    return result;
}

/* Bigint power function */
bigint *bigint_pow(bigint *a, bigint *b) {
    bigint *result, *i, *one, *previous;

    i = create_bigint(b->length);
    one = create_bigint_from_string("1");
    result = create_bigint_from_string("1");
    previous = result;

    while (bigint_compare(i, b) < 0) {
        result = bigint_multiply(previous, a);
        bigint_clear(previous);
        previous = result;

        i = bigint_add(i, one);
        bigint_print(i);
        printf(" / ");
        bigint_print(b);
        printf("\n");
    }

    bigint_clear(i);
    bigint_clear(one);
    bigint_clear(previous);

    return result;
}

/* Returns 1 if a is bigger, -1 if b is bigger, or 0 if they are equal */
int bigint_compare(bigint *a, bigint *b) {
    if (a->length > b->length)
        return 1;
    else if (a->length < b->length)
        return -1;
    else
        return bigint_compare_helper(a, b, a->length);
}

/* Recursive function used by bigint_compare */
int bigint_compare_helper(bigint *a, bigint *b, int length) {
    if (a->digits[length-1] > b->digits[length-1])
        return 1;
    else if (a->digits[length-1] < b->digits[length-1])
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
int custom_pow(int a, int b) {
    int res = 1, i;
    for (i = 0; i < b; i++)
        res *= a;

    return res;
}
