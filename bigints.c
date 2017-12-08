#include "bigints.h"

/* Creates an empty bigint with defined length */
bigint *create_bigint (int base, int length) {
    bigint *b;

    /* allocate memory for 1 bigint */
    b = (bigint *)calloc(1, sizeof(bigint));
    if (b != NULL) {
        b->base = base;
        b->length = 1;
        b->max_digits = length;
        /* allocate length amount of digits */
        b->digits = (uint8_t*)calloc(length, sizeof(uint8_t));
    }

    return b;
}

/* Creates a bigint from a string */
bigint *create_bigint_from_string(int base, char *string) {
    bigint *b;
    int i, ph, str_index = 0, str_length, digits = 0, number_int;
    char *str_pos;

    /* store input string's length */
    str_length = strlen(string);

    if (base <= 10) {
        /* for bases up to 10, use length directly */
        digits = str_length;
    }
    else {
        /* for bases greater than 10, count amount of ':' characters instead */
        str_pos = string;
        while (str_pos != NULL && str_pos < string + str_length) {
            /* set str_pos to position after next ':' */
            str_pos = strchr(str_pos + 1, ':');

            /* if a ':' was found, increment digits*/
            if (str_pos != NULL)
                digits++;
        }
    }

    /* create bigint and set its length to digit amount */
    b = create_bigint(base, digits);
    b->length = b->max_digits;

    /* reset str_pos */
    str_pos = string - 1;

    /* count down from last digit, to zero */
    for (i = b->max_digits - 1; i >= 0; i--) {
        if (base <= 10) {
            /* for bases up to 10, convert current char to integer */
            ph = char_to_int(string[str_index]);
            /* set current digit to that integer */
            b->digits[i] = ph;
            /* increment string index */
            str_index++;
        }
        else
        {
            /* for bases greater than 10, scan digit without the ':' */
            sscanf(str_pos + 1, "%d:", &number_int);
            /* set current digit to scanned integer */
            b->digits[i] = (uint8_t)number_int;
            /* set str_pos to position after next ':' */
            str_pos = strchr(str_pos + 1, ':');
        }
    }

    return b;
}

/* Creates a copy of b and returns a pointer to it */
bigint *create_bigint_copy(bigint *b) {
    int i;
    bigint *copy;

    /* allocate memory for 1 bigint */
    copy = (bigint *)calloc(1, sizeof(bigint));

    /* copy variables from b to copy */
    copy->base = b->base;
    copy->length = b->length;
    copy->max_digits = b->max_digits;

    /* allocate length amount of digits */
    copy->digits = (uint8_t*)calloc(b->max_digits, sizeof(uint8_t));

    /* copy each digit from b to copy */
    for (i = 0; i < b->length; i++) {
        copy->digits[i] = b->digits[i];
    }

    return copy;
}

/* Creates a version of b in a different base
   The i parameters should be each digit in new_base with leading zeroes */
bigint *bigint_convert_base(bigint *b, int new_base, int i2, int i1, int i0){
    bigint *converted, *base, *temp_divide, *temp_divide_prev, *temp_mod;
    int digit = 0, base_length, converted_max_length;

    /* determine how many digits new_base contains */
    if (i2 > 0)
        base_length = 3;
    else if (i1 > 0)
        base_length = 2;
    else
        base_length = 1;

    /* create bigint to store new_base and set its length to base_length */
    base = create_bigint(b->base, base_length);
    base->length = base_length;

    /* set each digit in base to i parameters */
    if (base_length > 2)
        base->digits[2] = i2;
    if (base_length > 1)
        base->digits[1] = i1;
    base->digits[0] = i0;

    /* find max length for converted number */
    converted_max_length = (int)ceil(b->length * log(b->base) / log(new_base));

    /* create bigint to store converted number */
    converted = create_bigint(new_base, converted_max_length);

    /* prepare variables */
    temp_divide = create_bigint_copy(b);
    temp_divide_prev = temp_divide;

    /* calculate result */
    while(bigint_compare(temp_divide, base) >= 0) {
        temp_mod = bigint_modulus(temp_divide, base);
        converted->digits[digit] = temp_mod->digits[0] + temp_mod->digits[1] * b->base + temp_mod->digits[2] * b->base * b->base;
        bigint_clear(&temp_mod);

        temp_divide = bigint_divide(temp_divide, base);
        bigint_clear(&temp_divide_prev);
        temp_divide_prev = temp_divide;

        digit++;
    }

    /* set converted number length */
    converted->length = digit + 1;

    temp_mod = bigint_modulus(temp_divide, base);
    converted->digits[digit] = temp_mod->digits[0] + temp_mod->digits[1] * b->base + temp_mod->digits[2] * b->base * b->base;
    bigint_clear(&temp_mod);

    return converted;
}

/* frees up a bigint's allocated memory */
void bigint_clear (bigint **b) {
    /* free digit array */
    free((*b)->digits);
    /* free bigint */
    free((*b));
    /* reset the bigint pointer */
    *b = NULL;
}

/* Prints bigint to standard output */
void bigint_print(bigint *b) {
    int i;
    char format[5];

    strcpy(format, (b->base <= 10) ? "%d" : "%d:" );

    for (i = b->length - 1; i >= 0; i--) {
        printf(format, b->digits[i]);
    }
}

/* Prints bigint to a string */
void bigint_print_string(char *str, bigint *b) {
    int i, j = 0;
    char format[5];

    strcpy(format, (b->base <= 10) ? "%d" : "%d:" );

    for (i = b->length - 1; i >= 0; i--) {
        sprintf(str+j, format, b->digits[i]);
        if (b->base <= 10)
            j++;
        else {
            if (b->digits[i] > 99)
                j += 4;
            else if (b->digits[i] > 9)
                j += 3;
            else
                j += 2;
        }
    }
}

/* Prints bigint to a file */
void bigint_print_file(FILE *file, bigint *b) {
    int i;
    char format[5];

    strcpy(format, (b->base <= 10) ? "%d" : "%d:" );

    for (i = b->length - 1; i >= 0; i--) {
        fprintf(file, format, b->digits[i]);
    }
}

/* Adds two bigints */
bigint *bigint_add(bigint *a, bigint *b) {
    bigint *result;
    int i, length, added, temp_a, temp_b;
	int mente = 0;

    length = (a->length > b->length) ? a->length : b->length;

    result = create_bigint(a->base, length + 1);

    for (i = 0; i < length; i++) {
        temp_a = (i < a->length) ? a->digits[i] : 0;
        temp_b = (i < b->length) ? b->digits[i] : 0;
        added = temp_a + temp_b + mente;

        if (added > (a->base - 1)) {
            result->digits[i] = added - a->base;
            mente = 1;
            if (i == length-1)
                length++;
        }
        else {
            result->digits[i] = (uint8_t)added;
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
    result = create_bigint(a->base, length);

    for (i = 0; i < length; i++) {
        /* use zero if i over length */
        temp_a = (i < a->length) ? a->digits[i] : 0;
        temp_b = (i < b->length) ? b->digits[i] : 0;

        borrow = (temp_a < temp_b || temp_a < mente) ? a->base : 0;
        subbed = temp_a - temp_b + borrow - mente;
        mente = (temp_a < temp_b || temp_a < mente) ? 1 : 0;

        if (subbed < 0) {
            subbed += a->base;
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
    int ia, ib, zeroes, initial_value, tempint, i, str_pos = 0;
    char str[MAX_DIGITS];
    uint8_t digits[MAX_DIGITS];

    /* result max digits is combined digit amount */
    result = create_bigint(a->base, a->length + b->length);

    if ((a->length == 1 && a->digits[0] == 0) ||
        (b->length == 1 && b->digits[0] == 0)) {
        /* multiplication by 0, therefore the result is 0 */
        return result;
    }

    previous = result;

    /* for each digit pair */
    for (ia = 0; ia < a->length; ia++) {
        for (ib = 0; ib < b->length; ib++) {
            /* multiply ints */
            initial_value = a->digits[ia] * b->digits[ib];
            tempint = initial_value;

            str_pos = 0;
            /* add result to string */
            if (a->base <= 10)
                sprintf(str, "%d", tempint);
            else if (tempint < a->base) {
                sprintf(str, "%d:", tempint);
            }
            else {
                i = 0;
                while (tempint >= a->base) {
                    digits[i] = tempint % a->base;
                    tempint = tempint / a->base;
                    i++;
                }
                digits[i] = tempint % a->base;
                tempint = tempint / a->base;
                i++;
                while (i > 0) {
                    i--;
                    sprintf(str + str_pos, "%d:", digits[i]);

                    if (digits[i] > 99)
                        str_pos += 4;
                    else if (digits[i] > 9)
                        str_pos += 3;
                    else
                        str_pos += 2;
                }
            }


            if (initial_value > 0) {
                /* add zeroes to end of string */
                for (zeroes = 0; zeroes < ia + ib; zeroes++) {
                    if (a->base <= 10)
                        strcat(str, "0");
                    else
                        strcat(str, "0:");
                }
            }

            /* make bigint from string, and add to overall result */
            temp = create_bigint_from_string(a->base, str);

            result = bigint_add(previous, temp);


            bigint_clear(&temp);

            bigint_clear(&previous);
            previous = result;
        }
    }

    return result;
}

/* Divides two bigints */
bigint *bigint_divide(bigint *a, bigint *b) {
    bigint *sum, *sum_prev, *subtractor, *times, *times_prev, *add_bigint;
    char b_str[MAX_DIGITS], add_str[MAX_DIGITS];
    int i, zeroes;

    times = create_bigint(a->base, a->length);
    times_prev = times;

    sum = create_bigint_copy(a);
    sum_prev = sum;

    do {
        memset(b_str, '\0', MAX_DIGITS);
        memset(add_str, '\0', MAX_DIGITS);
        bigint_print_string(b_str, b);

        if(a->base <= 10)
            strcpy(add_str, "1");
        else
            strcpy(add_str, "1:");

        if (sum->length > b->length + 1) {
            zeroes = sum->length - b->length - 1;

            for (i = 0; i < zeroes; i++)
            {
                if (a->base <= 10) {
                    strcat(b_str, "0");
                    strcat(add_str, "0");
                }
                else {
                    strcat(b_str, "0:");
                    strcat(add_str, "0:");
                }
            }
        }

        add_bigint = create_bigint_from_string(a->base, add_str);
        subtractor = create_bigint_from_string(a->base, b_str);
        sum = bigint_subtract(sum, subtractor);
        times = bigint_add(times, add_bigint);

        bigint_clear(&times_prev);
        bigint_clear(&subtractor);
        bigint_clear(&sum_prev);

        times_prev = times;
        sum_prev = sum;
    }
    while (bigint_compare(sum, b) >= 0);

    return times;
}

/* a % b */
bigint *bigint_modulus(bigint *a, bigint *b) {
    bigint *result, *previous, *subtractor;
    char b_str[MAX_DIGITS];
    int i, zeroes;

    if (a->length < b->length) {
        return create_bigint_copy(a);
    }
    else if (a->length == b->length && bigint_compare(a,b) == -1){
        return create_bigint_copy(a);
    }
    else {
        result = create_bigint_copy(a);

        previous = result;

        do {
            memset(b_str, '\0', MAX_DIGITS);
            bigint_print_string(b_str, b);

            if (result->length > b->length + 1) {
                zeroes = result->length - b->length - 1;

                for (i = 0; i < zeroes; i++)
                {
                    if (a->base <= 10)
                        strcat(b_str, "0");
                    else
                        strcat(b_str, "0:");
                }
            }

            subtractor = create_bigint_from_string(a->base, b_str);
            result = bigint_subtract(previous, subtractor);

            bigint_clear(&subtractor);
            bigint_clear(&previous);

            previous = result;
        }
        while (bigint_compare(result, b) >= 0);

        return result;
    }
}

/* Bigint power function */
bigint *bigint_pow(bigint *a, bigint *b) {
    bigint *zero, *one, *two,
    *result, *subtracted, *multiplied, *divided, *mod, *raised;
    char number[3];

    /* create 0 as bigint in current base */
    sprintf(number, (a->base <= 10) ? "%d" : "%d:", 0);
    zero = create_bigint_from_string(a->base, number);

    /* create 1 as bigint in current base */
    sprintf(number, (a->base <= 10) ? "%d" : "%d:", 1);
    one = create_bigint_from_string(a->base, number);

    /* create 2 as bigint in current base */
    sprintf(number, (a->base <= 10) ? "%d" : "%d:", 2);
    two = create_bigint_from_string(a->base, number);

    /* if b is greater than 1 */
    if (bigint_compare(b, one) == 1) {
        /* b % 2 */
        mod = bigint_modulus(b, two);

        /* if b is even */
        if (bigint_compare(mod, zero) == 0) {
            bigint_clear(&one);
            bigint_clear(&mod);
            bigint_clear(&zero);

            /* a * a  */
            multiplied = bigint_multiply(a, a);

            /* b / 2 */
            divided = bigint_divide(b,two);
            bigint_clear(&two);

            /* (a * a) ^ (b / 2) */
            result = bigint_pow(multiplied, divided);
            bigint_clear(&multiplied);
            bigint_clear(&divided);

            return result;
        }
        /* if b is odd */
        else {
            bigint_clear(&mod);
            bigint_clear(&zero);

            /* a * a  */
            multiplied = bigint_multiply(a, a);

            /* b - 1 */
            subtracted = bigint_subtract(b, one);
            bigint_clear(&one);

            /* (b - 1) / 2 */
            divided = bigint_divide(subtracted, two);
            bigint_clear(&subtracted);
            bigint_clear(&two);

            /* (a * a) ^ ( (b - 1) / 2 ) */
            raised = bigint_pow(multiplied, divided);
            bigint_clear(&multiplied);
            bigint_clear(&divided);

            /* a * ( (a * a) ^ ( (b - 1) / 2 ) ) */
            result = bigint_multiply(a, raised);
            bigint_clear(&raised);

            return result;
        }
    }
    /* if b is 1 */
    else if(bigint_compare(b, one) == 0) {
        bigint_clear(&two);
        bigint_clear(&zero);
        bigint_clear(&one);

        /* result is a */
        result = create_bigint_copy(a);

        return result;
    }
    /* if b is 0 (we do not support negative numbers) */
    else {
        bigint_clear(&two);
        bigint_clear(&zero);

        /* result is 1 */
        result = create_bigint_copy(one);
        bigint_clear(&one);

        return result;
    }
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
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
    }
    return -1;
}

/*
    OLD FUNCTIONS
*/

int custom_pow(int a, int b) {
    int res = 1, i;
    for (i = 0; i < b; i++)
        res *= a;

    return res;
}

/*
bigint *bigint_multiply_old(bigint *a, bigint *b) {
    int i, j;
    bigint *result;
    result = create_bigint_from_string(a->base, "0");

    for (i = 0; i < b->length; i++) {
        for (j = 0; j < custom_pow(a->base, i) * b->digits[i]; j++) {
            result = bigint_add(result, a);
        }
    }

    return result;
}

bigint *bigint_divide(bigint *a, bigint *b) {
    bigint *sum, *prev_sum, *times, *prev_times, *one;
    int sum_length;

    sum_length = (a->length > b->length) ? a->length : b->length;

    sum = create_bigint(a->base, sum_length + 1);
    times = create_bigint(a->base, a->length);

    if (a->base <= 10)
        one = create_bigint_from_string(a->base, "1");
    else
        one = create_bigint_from_string(a->base, "1:");

    prev_sum = sum;
    prev_times = times;
    while (bigint_compare(sum, a) < 0) {
        sum = bigint_add(prev_sum, b);
        times = bigint_add(prev_times, one);

        bigint_clear(&prev_times);
        bigint_clear(&prev_sum);

        prev_sum = sum;
        prev_times = times;
    }

    if (bigint_compare(sum, a) > 0)
        times = bigint_subtract(times, one);

    bigint_clear(&one);
    bigint_clear(&sum);

    return times;
}

bigint *bigint_modulus_old(bigint *a, bigint *b) {
    bigint *result;

    result = create_bigint(a->base, b->length);

    while (bigint_compare(result, a) < 0) {
        result = bigint_add(result, b);
    }

    if (bigint_compare(result, a) > 0)
        result = bigint_subtract(result, b);

    result = bigint_subtract(a, result);

    return result;
}

bigint *bigint_pow(bigint *a, bigint *b) {
    bigint *result, *i, *one, *previous, *prev_i;

    i = create_bigint(a->base, b->length);

    if (a->base <= 10) {
        one = create_bigint_from_string(a->base, "1");
        result = create_bigint_from_string(a->base, "1");
    }
    else {
        one = create_bigint_from_string(a->base, "1:");
        result = create_bigint_from_string(a->base, "1:");
    }

    previous = result;
    prev_i = i;

    while (bigint_compare(i, b) < 0) {
        result = bigint_multiply(previous, a);
        i = bigint_add(prev_i, one);

        bigint_clear(&previous);
        previous = result;

        bigint_clear(&prev_i);
        prev_i = i;
    }

    bigint_clear(&one);
    bigint_clear(&prev_i);

    return result;
}
*/
