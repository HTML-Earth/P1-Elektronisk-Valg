#include "longint.h"

longint *create_longint (int base, int length) {
    longint *l;

    /* allocate memory for 1 bigint */
    l = (longint *)calloc(1, sizeof(longint));
    if (l != NULL) {
        l->max_digits = length;
        l->base = base;
        /* allocate length amount of digits */
        l->digit = (uint16_t *)calloc(length, sizeof(uint16_t));
    }

    return l;
}

longint *direct_longint_from_string(char *string) {
    longint *b;
    uint16_t str_length, digits = 0, number_int;
    int i;
    char *str_pos;

    /* store input string's length */
    str_length = strlen(string);

    /* for bases greater than 10, count amount of ':' characters instead */
    str_pos = string;
    while (str_pos != NULL && str_pos < string + str_length) {
    /* set str_pos to position after next ':' */
      str_pos = strchr(str_pos + 1, ':');

        /* if a ':' was found, increment digits*/
      if (str_pos != NULL){
          digits++;
      }
    }

    /* create bigint and set its length to digit amount */
    b = create_longint(256, digits);

    /* reset str_pos */
    str_pos = string - 1;

    /* count down from last digit, to zero */
    for (i = b->max_digits - 1; i >= 0; i--) {
            /* for bases greater than 10, scan digit without the ':' */
            sscanf(str_pos + 1, "%hu:", &number_int);
            /* set current digit to scanned integer */
            b->digit[i] = number_int;
            /* set str_pos to position after next ':' */
            str_pos = strchr(str_pos + 1, ':');

    }

    return b;
}

longint *create_base10_from_string(int base, char *string){
  longint *l;
  int i, ph, str_index = 0, str_length, digits = 0;

  str_length = strlen(string);

  digits = str_length;

  l = create_longint(base, digits);

  for (i = l->max_digits - 1; i >= 0; i--) {
    ph = char_to_int(string[str_index]);
    l->digit[i] = ph;
    str_index++;
  }
  return l;
}


longint *create_longint_from_string(char *str){
  longint *l, *temp;

  temp = create_base10_from_string(10, str);
  l = recursive_binary_conversion(temp);

  longint_clear(&temp);

  return l;
}

longint *create_longint_copy(longint *b) {
    int i;
    longint *copy;

    /* allocate memory for 1 bigint */
    copy = (longint *)calloc(1, sizeof(longint));

    /* copy variables from b to copy */
    copy->base = b->base;
    copy->max_digits = b->max_digits;

    /* allocate length amount of digits */
    copy->digit = (uint16_t*)calloc(b->max_digits, sizeof(uint16_t));

    /* copy each digit from b to copy */
    for (i = 0; i < b->max_digits; i++) {
        copy->digit[i] = b->digit[i];
    }

    return copy;
}


void longint_clear (longint **b){
    /* free digit array */
  free((*b)->digit);
    /* free bigint */
  free((*b));
    /* reset the bigint pointer */
  *b = NULL;
}


void longint_print(longint *l){
    int i;

    if(l->base == 256){
      for (i = l->max_digits-1; i >= 0; i--) {
        printf("%hu:", l->digit[i]);
      }
    }
    else{
      for (i = l->max_digits-1; i >= 0; i--) {
          printf("%hu", l->digit[i]);
      }
    }
    printf("\n");
}

void longint_print_string(char *str, longint *l){
    int i, j = 0;
    char format[5];

    strcpy(format, (l->base <= 10) ? "%hu" : "%hu:" );

    for (i = l->max_digits - 1; i >= 0; i--) {
        sprintf(str+j, format, l->digit[i]);
        if(l->base <= 10){
          j++;
        }
        else{
          if(l->digit[i] > 9999)
              j += 6;
          else if (l->digit[i] > 999)
              j += 5;
          else if (l->digit[i] > 99)
              j += 4;
          else if (l->digit[i] > 9)
              j += 3;
          else
              j += 2;
        }
    }
}

longint *convert_base10_to_longint(char *str){
    longint *converted;
    longint *b, *base, *temp_divide, *temp_divide_prev, *temp_mod;
    long converted_max_length;
    int index = 0;


    b = create_base10_from_string(10, str);

    base = create_base10_from_string(10,"256");

    converted_max_length = (long)ceil(b->max_digits * log(10) / log(256));

    converted = create_longint(256, converted_max_length);

    temp_divide = create_longint_copy(b);
    temp_divide_prev = temp_divide;

    while(longint_compare(temp_divide, base) >= 0) {
        temp_mod = longint_modulus(temp_divide, base);
        converted->digit[index] = conversion_value(temp_mod);
        longint_clear(&temp_mod);
        temp_divide = longint_divide(temp_divide, base);
        longint_clear(&temp_divide_prev);
        temp_divide_prev = temp_divide;


        index++;
    }

    converted->max_digits = index + 1;

    temp_mod = longint_modulus(temp_divide, base);
    converted->digit[index] = conversion_value(temp_mod);
    longint_clear(&b);
    longint_clear(&base);
    longint_clear(&temp_mod);
    longint_clear(&temp_divide_prev);


    return converted;
}

longint *recursive_binary_conversion(longint *l){
  uint32_t n, k, i, j = 0;
  uint32_t converted_max_length;
  longint *x_high, *x_low, *x_high_prev, *x_low_prev, *converted, *b_pow, *base, *k_int;
  char k_str[10];

  base = direct_longint_from_string("10:");

  converted_max_length = (uint32_t)ceil(l->max_digits * log(10) / log(256));

  converted = create_longint(256, converted_max_length);

  n = l->max_digits;

  if(n < 2){
    converted->digit[0] += l->digit[0];
  }
  else{
    k = n / 2;
    itoa(k, k_str, 10);
    k_int = create_longint_from_string(k_str);
    b_pow = longint_power(base, k_int);

    x_low = create_longint(256, k);
    x_high = create_longint(256, n-k);

    for(i = 0; i < k; i++){
      x_low->digit[i] = l->digit[i];
    }

    for(i = k; i < n; i++){
      x_high->digit[j] = l->digit[i];
      j++;
    }


    x_low_prev = x_low;
    x_high_prev = x_high;

    x_low = recursive_binary_conversion(x_low);
    x_high = recursive_binary_conversion(x_high);

    longint_clear(&x_low_prev);
    longint_clear(&x_high_prev);

    converted = longint_add(longint_multiply(x_high, b_pow), x_low);
  }
  while(converted->max_digits-1 > 0 && converted->digit[converted->max_digits-1] == 0){
    converted->max_digits--;
  }
  return converted;
}

longint *recursive_radix_conversion(longint *l){
  uint16_t n, k, i, j = 0;
  uint16_t converted_max_length;
  longint *x_high, *x_low, *x_high_prev, *x_low_prev, *converted, *b_pow, *base, *k_int;
  char k_str[10000];

  base = create_base10_from_string(10,"256");

  converted_max_length = (uint16_t)ceil(l->max_digits * log(256) / log(10)+10);

  converted = create_longint(10, converted_max_length);

  n = l->max_digits;

/*  printf("n was here %hu\n", n);*/

  if(n < 2){
    converted->digit[0] = l->digit[0];
    /*printf("digit stored in place 0 was %hu\n", converted->digit[0]);*/
    if (converted->digit[0] > 9){
      for(i = 0; i < converted->max_digits; i++){
        converted->digit[i+1] = converted->digit[i] / 10;
        converted->digit[i] = converted->digit[i] % 10;
        /*printf("digit stored in place %hu was %hu and digit stored in place %hu, was %hu\n",i, converted->digit[i], i+1, converted->digit[i+1]);*/
      }
    }
  }
  else{
    k = n / 2;
    itoa(k, k_str, 10);
    k_int = create_base10_from_string(10, k_str);
    b_pow = longint_power(base, k_int);

    /*printf("b_pow became:\n");
    longint_print(b_pow);*/

    x_low = create_longint(10, k);
    x_high = create_longint(10, n-k);

    for(i = 0; i < k; i++){
      x_low->digit[i] = l->digit[i];
    }

    for(i = k; i < n; i++){
      x_high->digit[j] = l->digit[i];
      j++;
    }
    /*printf("x_low became:\n");
    longint_print(x_low);
    printf("x_high became:\n");
    longint_print(x_high);
*/
    x_low_prev = x_low;
    x_high_prev = x_high;

    x_low = recursive_radix_conversion(x_low);
    x_high = recursive_radix_conversion(x_high);

    longint_clear(&x_low_prev);
    longint_clear(&x_high_prev);

    converted = longint_add(longint_multiply(x_high, b_pow), x_low);

  }
  /*printf("converted became:\n");
  longint_print(converted);*/
  while(converted->max_digits-1 > 0 && converted->digit[converted->max_digits-1] == 0){
    converted->max_digits--;
  }
  return converted;
}

/*
bigint *convert_longint_to_bigint(longint *l){
    bigint *converted;
    bigint *base, *temp_divide, *temp_divide_prev, *temp_mod;
    long converted_max_length;
    int i, index = 0;

    base = create_bigint_from_string(10,"10");

    converted_max_length = (long)ceil(l->max_digits * log(256) / log(10));
    printf("converted max lenth set to = %ld\n", converted_max_length);

    printf("i am here\n");
    converted = create_bigint(10, converted_max_length);

    printf("ready to copy\n");

    temp_divide = create_bigint_copy_from_longint(l);
    temp_divide_prev = temp_divide;

    printf("ready to convert\n");

    while(bigint_compare(temp_divide, base) >= 0) {
        temp_mod = bigint_modulus(temp_divide, base);
        for (i = 0; i < temp_mod->length; i++) {
          converted->digits[index] += (uint16_t) ceil(temp_mod->digits[i] * power((long double)256,(long double)i));
        }

        bigint_clear(&temp_mod);

        temp_divide = bigint_divide(temp_divide, base);
        bigint_clear(&temp_divide_prev);
        temp_divide_prev = temp_divide;

        index++;
    }

    converted->length = index + 1;

    temp_mod = bigint_modulus(temp_divide, base);
    for (i = 0; i < temp_mod->length; i++) {
      converted->digits[index] += (long) ceil(temp_mod->digits[i] * power((long double)256,(long double)i));
    };
    bigint_clear(&temp_mod);
    bigint_clear(&temp_divide_prev);
    bigint_clear(&temp_divide);

    return converted;
}
*/

uint16_t conversion_value(longint *b){
  char temp_value [100];
  int i = 0, j = 0;
  uint16_t temp_int = 0;

  for(i = b->max_digits-1; i >= 0; i--){
    itoa(b->digit[i], temp_value+j, 10);
    j++;
  }

 temp_int = atoi(temp_value);

 return temp_int;
}

bigint *create_bigint_copy_from_longint(longint *b) {
    int i;
    bigint *copy;

    /* allocate memory for 1 bigint */
    copy = (bigint *)calloc(1, sizeof(bigint));

    /* copy variables from b to copy */
    copy->base = 10;
    copy->length = b->max_digits;
    copy->max_digits = b->max_digits;

    /* allocate length amount of digits */
    copy->digits = (uint8_t*)calloc(b->max_digits, sizeof(uint8_t));

    /* copy each digit from b to copy */
    for (i = 0; i < b->max_digits; i++) {
        copy->digits[i] = b->digit[i];
    }

    return copy;
}

long double power(long double number, long double pow){
  long double result;

  if (pow == 0)
    result = 1;
  else if (pow > 0 && !(odd(pow)))
    result = sqr(power(number,pow/2));
  else if (pow > 0 && odd(pow))
    result = number * power(number, pow - 1);
  else
    result = 1 / power(number, -pow);

  return result;
}

int odd(long double pow){
  unsigned long n;
  n = pow;
  return n & 1;
}

long double sqr(long double pow){
  return pow * pow;
}
/*
char *longint_base10_convertion(longint *l){
  char *converted;
  longint *base, *temp_divide, *temp_divide_prev, *temp_mod;
  long converted_max_length;
  int i, index = 0;

  converted_max_length = (long)ceil(b->length * log(4294967295) / log(10));

  converted = (char *)calloc(converted_max_length, sizeof(char));

  temp_divide = create_longint_copy(b);
  temp_divide_prev = temp_divide;

  while(bigint_compare(temp_divide, base) >= 0) {
      temp_mod = bigint_modulus(temp_divide, base);
      for (i = 0; i < temp_mod->length; i++) {
        converted->digit[index]= (long) ceil(temp_mod->digits[i] * pow(10,i));
      }

      bigint_clear(&temp_mod);

      temp_divide = bigint_divide(temp_divide, base);
      bigint_clear(&temp_divide_prev);
      temp_divide_prev = temp_divide;

      index++;
  }

  converted->max_digits = index + 1;

  temp_mod = bigint_modulus(temp_divide, base);
  for (i = 0; i < temp_mod->length; i++) {
    converted->digit[index] += (long) ceil(temp_mod->digits[i] * pow(10,i));
  };
  bigint_clear(&temp_mod);
  bigint_clear(&temp_divide_prev);
  bigint_clear(&temp_divide);

  return converted;
}



}
*/

longint *longint_add(longint *a, longint *b) {
  longint *result;
  int i, length;
  uint32_t s, c, d = 0, maske = 255;

  length = (a->max_digits > b->max_digits) ? a->max_digits : b->max_digits;

  result = create_longint(a->base, length);

  if(a->base == 256){
    for (i = 0; i < length; i++) {
      s = ((i < a->max_digits) ? a->digit[i] : 0) + ((i < b->max_digits) ? b->digit[i] : 0) + d;
      c = s & maske;
      result->digit[i] = c;
      d = s >> 8;
      if(d == 1  && i == length-1){
        length++;
      }
    }
  }
  else if(a->base == 10){
    for (i = 0; i < length; i++) {
      s = ((i < a->max_digits) ? a->digit[i] : 0) + ((i < b->max_digits) ? b->digit[i] : 0) + d;
      c = s % 10;
      result->digit[i] = c;
      d = s / 10;
      if(d == 1  && i == length-1){
        length++;
      }
    }
  }

  result->max_digits = length;

  return result;
}

longint *longint_subtract(longint *a, longint *b) {
    longint *result;
    int i, length;
    long s, d = 0, base = a->base;

    /* result max_digits is length of longest parameter */
    length = (a->max_digits > b->max_digits) ? a->max_digits : b->max_digits;

    /* create result variable */
    result = create_longint(a->base, length);
      if(longint_compare(a,b) == -1){
        return result;
      }

    for (i = 0; i < length; i++) {
      s =  ((i < a->max_digits) ? a->digit[i] : 0) - ((i < b->max_digits) ? b->digit[i] : 0) - d;
      if(s < 0){
        s += base;
        d = 1;
      }
      else{
        d = 0;
      }
      result->digit[i] = s;
    }

    while(result->max_digits-1 > 0 && result->digit[result->max_digits-1] == 0){
      result->max_digits--;
    }

    return result;
}

/*
longint *longint_karasuba(longint *l1, longint *l2){
  longint *a0, *a1, *b0, *b1, *c0, *c1, *c2, *k, *k2, *k_pow, *k_pow2, *two, *ln, *base;
  char cn[MAX_DIGITS], base_str[10], two_str[10];
  int n;

  strcpy(base_str, "1:0:");
  strcpy(two_str, "2:");

  base = create_longint_from_string(base_str);

  n = (l1->max_digits > l2->max_digits) ? l1->max_digits : l2->max_digits;
  itoa(n, cn, 10);

  ln = create_longint_from_string(cn);
  printf("ln became\n");
  longint_print(ln);
  two = direct_longint_from_string(two_str);

  if(n < 2){
    return longint_multiply(l1,l2);
  }

  else{
    k = longint_divide(ln, two);
    k2 = longint_multiply(k, two);
    k_pow = longint_power(base, k);
    k_pow2 = longint_power(base, k2);

    a0 = longint_modulus(l1, k_pow);
    b0 = longint_modulus(l2, k_pow);

    a1 = longint_divide(l1, k_pow);
    b1 = longint_divide(l2, k_pow);


    c0 = longint_karasuba(a0, b0);
    c1 = longint_karasuba(a1, b1);

    c2 = longint_subtract(longint_subtract(longint_multiply(longint_add(a0,a1), longint_add(b0,b1)), c0),c1);

    return longint_add(longint_add(longint_multiply(c1, k_pow2), longint_multiply(c2, k_pow)), c0);
  }

}
*/


int longint_compare(longint *a, longint *b) {
    if (a->max_digits > b->max_digits)
        return 1;
    else if (a->max_digits < b->max_digits)
        return -1;
    else
        return longint_compare_helper(a, b, a->max_digits);
}

/* Recursive function used by longint_compare */
int longint_compare_helper(longint *a, longint *b, int max_digits) {
    if (a->digit[max_digits-1] > b->digit[max_digits-1])
        return 1;
    else if (a->digit[max_digits-1] < b->digit[max_digits-1])
        return -1;
    else {
        if (max_digits < 2)
            return 0;
        else
            return longint_compare_helper(a, b, max_digits-1);
    }
}

longint *longint_multiply(longint *a, longint *b){
    longint *result;
    uint32_t temp, maske = 255;
    int ia, ib, i;

    result = create_longint(a->base, a->max_digits + b->max_digits);

    if ((a->max_digits == 1 && a->digit[0] == 0) ||
        (b->max_digits == 1 && b->digit[0] == 0)) {
        /* multiplication by 0, therefore the result is 0 */
        return result;
    }

    if(a->base == 256){
      for (ia = 0; ia < a->max_digits; ia++) {
          for (ib = 0; ib < b->max_digits; ib++) {
              /* multiply ints */

              if(ia == 0 && ib == 0){
                temp = a->digit[ia] * b->digit[ib];
                /*printf("one digit numbers - %hu + %hu = %hu \n", a->digit[ia], b->digit[ib], temp);*/
                result->digit[ia] += temp & maske;
                result->digit[ia+1] += temp >> 8;
              }
              else{
                temp = a->digit[ia] * b->digit[ib];
                /*printf("not one digit numbers - %hu + %hu = %hu \n", a->digit[ia] * b->digit[ib], temp);*/
                result->digit[ia+ib] += temp & maske;
                result->digit[ia+ib+1] += temp >> 8;
              }
          }
      }
      for(i = 0; i < result->max_digits;i++){
        if(result->digit[i] >= 256){
          temp = result->digit[i];
          result->digit[i] = temp & maske;
          result->digit[i+1] += temp >> 8;
        }
      }
  }
  else if(a->base == 10){
    for (ia = 0; ia < a->max_digits; ia++) {
        for (ib = 0; ib < b->max_digits; ib++) {

            if(ia == 0 && ib == 0){
              temp = a->digit[ia] * b->digit[ib];
              result->digit[ia] += temp % 10;
              result->digit[ia+1] += temp / 10;
            }
            else{
              temp = a->digit[ia] * b->digit[ib];
              result->digit[ia+ib] += temp % 10;
              result->digit[ia+ib+1] += temp / 10;
            }
        }
    }
    for(i = 0; i < result->max_digits;i++){
      if(result->digit[i] >= 10){
        result->digit[i+1] += result->digit[i] / 10;
        result->digit[i] = result->digit[i] % 10;
      }
    }
  }
  while(result->max_digits-1 > 0 && result->digit[result->max_digits-1] == 0){
    result->max_digits--;
  }

  return result;
}

/*
longint *longint_basecase_divide(longint *a, longint *b){
  int n, m, j, q_counter;
  unsigned long q_temp_int, base_int = a->base;
  char j_str[10], b_str[10], m_str[10], q_temp_char[10];
  longint *r_res, *q_res, *a_temp, *a_temp_prev, *base, *j_int, *j_int_prev, *m_int, *b_pow, *a_check, *q_temp, *subtractor, *sub_prev;

  q_res = create_longint(a->base, a->max_digits);

  if((b->max_digits == 1 && b->digit[0] == 0) || (longint_compare(a,b) == -1)){
    return q_res;
  }

  else{

    q_temp = create_longint(a->base, 1);
    a_temp = create_longint_copy(a);
    a_temp_prev = a_temp;

    itoa(a->base, b_str, 10);
    base = create_longint_from_string(b_str);

    n = b->max_digits+1;
    m = a->max_digits - b->max_digits;
    itoa(a->base, m_str, 10);
    m_int = create_longint_from_string(m_str);


    j = m-1;
    itoa(j, j_str, 10);
    j_int = create_longint_from_string(j_str);

    b_pow = longint_power(base, m_int);
    a_check = longint_multiply(b_pow, b);

    if(longint_compare(a, b_pow) == 1){
      q_res->digit[m] = 1;
      a_temp = longint_subtract(a_temp, a_check);
    }

    longint_clear(&b_pow);
    longint_clear(&a_check);
    longint_clear(&a_temp_prev);
    longint_clear(&j_int);

    for(j = j; j >= 0; j--){
      itoa(j, j_str, 10);
      j_int = create_longint_from_string(j_str);
      b_pow = longint_power(base, j_int);

      q_temp_int = (((n+j > a_temp->max_digits) ? 0 : a_temp->digit[n+j-1]) * base_int + ((n+j-1 > a_temp->max_digits-1) ? 0 : a_temp->digit[n+j-2])) / b->digit[n-1];

      q_temp->digit[0] = (q_temp_int > base_int-1) ?  base_int-1 : q_temp_int;
      q_res->digit[j] = q_temp->digit[0];

      subtractor = longint_multiply(longint_multiply(q_temp,b_pow),b);

      if(longint_compare(a_temp, subtractor) == 1){
        subtractor = longint_subtract(subtractor, a_temp);
        indsæt statement om a

      }





    }

    return q_res;
  }
}
*/

/* scrapped because we cannot handle negative values */
/*
longint *recursive_divrem(longint *a, longint *b, longint *rem){
  int m, k, two_k;
  longint *Q, *q1, *q0, *r1, *r0, *b1, *b0, *aa, *aaa, *bk, *b2k, *base, *lk, *l2k, *zero, *one;
  char k_str[1000], k2_str[1000];
  m = a->max_digits-b->max_digits;
  Q = create_longint(b->base, b->max_digits+1);
  base = direct_longint_from_string("1:0:");
  zero = direct_longint_from_string("0:");
  one = direct_longint_from_string("1:");

    if(b->max_digits > a->max_digits){
      return Q;
    }
    else if(m < 2){
      rem = longint_modulus(a,b);
      return longint_divide(a,b);
    }
  else{
    k = m/2;
    two_k = 2*k;
    itoa(k_str, k, 10);
    itoa(k2_str, two_k, 10);
    lk = direct_longint_from_string(k_str);
    l2k = direct_longint_from_string(k2_str);

    bk = longint_power(base, lk);
    b2k = longint_power(base, l2k);

    b1 = longint_divide(b, bk);
    b0 = longint_modulus(b, bk);

    q1 = recursive_divrem(longint_divide(a, l2k), b1, r1);

    aa = longint_subtract(longint_add(longint_multiply(r1, b2k), longint_modulus(a, b2k)), longint_multiply(q1, longint_multiply(b0, bk)));

    while(longint_compare(aa, zero) == -1){
      q1 = longint_subtract(q1, one);
      aa = longint_add(aa, longint_multiply(b, bk));
    }

    q0 = recursive_divrem(longint_divide(aa, bk), b1, r0);

    aaa = longint_subtract(longint_add(longint_multiply(r0, bk), longint_modulus(aa, bk)), longint_multiply(q0, b0));

    while(longint_compare(aaa, zero) == -1){
      q0 = longint_subtract(q0, one);
      aaa = longint_add(aaa,b);
    }

    rem = aaa;
    return longint_add(longint_multiply(q1, bk), q0);

  }
}
*/
/*
longint *longint_multiply(longint *a, longint *b) {
    longint *result;
    long ia, ib, ph1 = 0, ph2 = 0, tempint = 0, i;


    result = create_longint(a->max_digits + b->max_digits);

    if ((a->max_digits == 1 && a->digit[0] == 0) ||
        (b->max_digits == 1 && b->digit[0] == 0)) {

        return result;
    }

    for (ia = 0; ia < a->max_digits; ia++) {
        for (ib = 0; ib < b->max_digits; ib++) {

            if(ia == 0 && ib == 0){
              result->digit[ia] += a->digit[ia] * b->digit[ib];
            }
            else{
              tempint = a->digit[ia] * b->digit[ib];

              if(ia == ib){
                result->digit[ia+ib] += tempint % 10;
                result->digit[ia+ib+1] += tempint / 10;
              }
              else{
                ph1 = (ia < ib) ? ib : ia;
                ph2 = (ia < ib) ? ia : ib;
                result->digit[ph1+ph2] += tempint % 10;
                result->digit[ph1+1+ph2] += tempint / 10;
              }
            }
        }
    }
    for(i = 0; i < result->max_digits;i++){
      if(result->digit[i] >= 10){
        result->digit[i+1] += result->digit[i] / 10;
        result->digit[i] = result->digit[i] % 10;
      }
    }

    return result;
}
*/
longint *longint_modulus(longint *a, longint *b) {
    longint *result, *previous, *subtractor;
    char b_str[MAX_DIGITS];
    int i, zeroes;

    if (a->max_digits < b->max_digits) {
        return create_longint_copy(a);
    }
    else if (a->max_digits == b->max_digits && longint_compare(a,b) == -1){
        return create_longint_copy(a);
    }
    else {
        result = create_longint_copy(a);

        previous = result;

        do {
            memset(b_str, '\0', MAX_DIGITS);
            longint_print_string(b_str, b);

            if (result->max_digits > b->max_digits + 1) {
                zeroes = result->max_digits - b->max_digits - 1;

                for (i = 0; i < zeroes; i++)
                {
                        strcat(b_str, "0:");
                }
            }

            subtractor = direct_longint_from_string(b_str);
            result = longint_subtract(previous, subtractor);

            longint_clear(&subtractor);
            longint_clear(&previous);

            previous = result;
        }
        while (longint_compare(result, b) >= 0);

        while(result->max_digits-1 > 0 && result->digit[result->max_digits-1] == 0){
          result->max_digits--;
        }

        return result;
    }
}

longint *longint_divide(longint *a, longint *b) {
    longint *sum, *sum_prev, *subtractor, *times, *times_prev, *add_longint;
    char b_str[MAX_DIGITS], add_str[MAX_DIGITS];
    int i, zeroes;

    times = create_longint(a->base, a->max_digits);
    times_prev = times;

    sum = create_longint_copy(a);
    sum_prev = sum;

    do {
        memset(b_str, '\0', MAX_DIGITS);
        memset(add_str, '\0', MAX_DIGITS);
        longint_print_string(b_str, b);

            strcpy(add_str, "1:");

        if (sum->max_digits > b->max_digits + 1) {
            zeroes = sum->max_digits - b->max_digits - 1;

            for (i = 0; i < zeroes; i++)
            {
                    strcat(b_str, "0:");
                    strcat(add_str, "0:");

            }
        }

        add_longint = direct_longint_from_string(add_str);
        subtractor = direct_longint_from_string(b_str);
        sum = longint_subtract(sum, subtractor);
        times = longint_add(times, add_longint);

        longint_clear(&times_prev);
        longint_clear(&subtractor);
        longint_clear(&sum_prev);

        times_prev = times;
        sum_prev = sum;
    }
    while (longint_compare(sum, b) >= 0);

    while(times->max_digits-1 > 0 && times->digit[times->max_digits-1] == 0){
      times->max_digits--;
    }


    return times;
}

/*
longint *longint_divide(longint *a, longint *b){
  longint *result, *temp_check, *base, *m;
  int temp_digits, n, m_int, j;
  char m_str[10];

  base = create_and_convert_longint_from_string("65536");

  temp_digits = (a->max_digits > b->max_digits) ? a->max_digits : b->max_digits;

  result = create_longint(temp_digits);


  if((b->max_digits == 1 && b->digit[0] == 0) || longint_compare(a,b) == -1){
    result = create_longint(temp_digits);
    return result;
  }

  else{
    n = b->max_digits;
    m_int = b->max_digits + a->max_digits;

    itoa(m, m_str,10);


    for(j = m_int-1, j >= 0; j--0){
      temp_check = longint_multiply(b, m);
      if(longint_compare(a, ))

    }



    return result;
  }
}
*/


longint *longint_power(longint *a, longint *b) {
    longint *zero, *one, *two,
    *result, *subtracted, *multiplied, *divided, *mod, *raised;
    char number[15];

    /* create 0 as longint in current base */
    sprintf(number, "%hu:", 0);
    zero = direct_longint_from_string(number);

    /* create 1 as longint in current base */
    sprintf(number, "%hu:", 1);
    one = direct_longint_from_string(number);

    /* create 2 as longint in current base */
    sprintf(number, "%hu:", 2);
    two = direct_longint_from_string(number);

    /* if b is greater than 1 */
    if (longint_compare(b, one) == 1) {
        /* b % 2 */
        mod = longint_modulus(b, two);

        /* if b is even */
        if (longint_compare(mod, zero) == 0) {
            longint_clear(&one);
            longint_clear(&mod);
            longint_clear(&zero);

            /* a * a  */
            multiplied = longint_multiply(a, a);

            /* b / 2 */
            divided = longint_divide(b,two);
            longint_clear(&two);

            /* (a * a) ^ (b / 2) */
            result = longint_power(multiplied, divided);
            longint_clear(&multiplied);
            longint_clear(&divided);

            return result;
        }
        /* if b is odd */
        else {
            longint_clear(&mod);
            longint_clear(&zero);

            /* a * a  */
            multiplied = longint_multiply(a, a);

            /* b - 1 */
            subtracted = longint_subtract(b, one);
            longint_clear(&one);

            /* (b - 1) / 2 */
            divided = longint_divide(subtracted, two);
            longint_clear(&subtracted);
            longint_clear(&two);

            /* (a * a) ^ ( (b - 1) / 2 ) */
            raised = longint_power(multiplied, divided);
            longint_clear(&multiplied);
            longint_clear(&divided);

            /* a * ( (a * a) ^ ( (b - 1) / 2 ) ) */
            result = longint_multiply(a, raised);
            longint_clear(&raised);

            return result;
        }
    }
    /* if b is 1 */
    else if(longint_compare(b, one) == 0) {
        longint_clear(&two);
        longint_clear(&zero);
        longint_clear(&one);

        /* result is a */
        result = create_longint_copy(a);

        return result;
    }
    /* if b is 0 (we do not support negative numbers) */
    else {
        longint_clear(&two);
        longint_clear(&zero);

        /* result is 1 */
        result = create_longint_copy(one);
        longint_clear(&one);

        return result;
    }
}

/*
longint *recursive_binary_conversion(longint)
*/

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
