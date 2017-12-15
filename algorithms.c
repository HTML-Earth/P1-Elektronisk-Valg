bigint *bigint_bit_multiply(bigint *a, bigint *b){
    bigint *result;
    uint32_t temp, maske = 255;
    int ia, ib, i;

    result = create_bigint(256, a->length + b->length);

    if ((a->length == 1 && a->digits[0] == 0) ||
        (b->length == 1 && b->digits[0] == 0)) {
        /* multiplication by 0, therefore the result is 0 */
        return result;
    }

    for (ia = 0; ia < a->length; ia++) {
        for (ib = 0; ib < b->length; ib++) {
            /* multiply ints */

            if(ia == 0 && ib == 0){
              temp = a->digits[ia] * b->digits[ib];
              /*printf("one digit numbers - %u + %u = %lu \n", a->digit[ia], b->digit[ib], temp);*/
              result->digits[ia] += temp & maske;
              result->digits[ia+1] += temp >> 8;
            }
            else{
              temp = a->digits[ia] * b->digits[ib];
              /*printf("not one digit numbers - %u + %u = %lu \n", a->digit[ia] * b->digit[ib], temp);*/

              if(ia == ib){
                result->digits[ia+ib] += temp & maske;
                result->digits[ia+ib+1] += temp >> 8;
              }
              else{
                result->digits[ia+ib] += temp & maske;
                result->digits[ia+ib+1] += temp >> 8;
              }
            }
        }
    }
    for(i = 0; i < result->length;i++){
      if(result->digits[i] >= 256){
        temp = result->digits[i];
        result->digits[i] = temp & maske;
        result->digits[i+1] += temp >> 8;
      }
    }
    while(result->length-1 > 0 && result->digits[result->length-1] == 0){
      result->length--;
    }

    return result;
}

bigint *bigint_recursive_divrem(bigint *a, bigint *b, bigint *rem){
  int m, k, two_k;
  bigint *Q, *q1, *q0, *r1, *r0, *b1, *b0, *aa, *aaa, *bk, *b2k, *base, *lk, *l2k, *zero, *one;
  char k_str[1000], k2_str[1000];
  m = a->length-b->length;
  Q = create_bigint(b->length+1);
  base = direct_bigint_from_string(base,"base");
  zero = direct_bigint_from_string(base,"0");
  one = direct_bigint_from_string(base,"1");

    if(b->length > a->length){
      return Q;
    }
    else if(m < 2){
      rem = bigint_modulus(a,b);
      return bigint_divide(a,b);
    }
  else{
    k = m/2;
    two_k = 2*k;
    itoa(k_str, k, 10);
    itoa(k2_str, two_k, 10);
    lk = direct_bigint_from_string(k_str);
    l2k = direct_bigint_from_string(k2_str);

    bk = bigint_power(base, lk);
    b2k = bigint_power(base, l2k);

    b1 = bigint_divide(b, bk);
    b0 = bigint_modulus(b, bk);

    q1 = recursive_divrem(bigint_divide(a, l2k), b1, r1);

    aa = bigint_subtract(bigint_add(bigint_bit_multiply(r1, b2k), bigint_modulus(a, b2k)), bigint_bit_multiply(q1, bigint_bit_multiply(b0, bk)));

    while(bigint_compare(aa, zero) == -1){
      q1 = bigint_subtract(q1, one);
      aa = bigint_add(aa, bigint_test_multiply(b, bk));
    }

    q0 = recursive_divrem(bigint_divide(aa, bk), b1, r0);

    aaa = bigint_subtract(bigint_add(bigint_bit_multiply(r0, bk), bigint_modulus(aa, bk)), bigint_bit_multiply(q0, b0));

    while(bigint_compare(aaa, zero) == -1){
      q0 = bigint_subtract(q0, one);
      aaa = bigint_add(aaa,b);
    }

    rem = aaa;
    return bigint_add(bigint_bit_multiply(q1, bk), q0);

  }
}

bigint *bigint_karasuba(bigint *l1, bigint *l2){
  bigint *a0, *a1, *b0, *b1, *c0, *c1, *c2, *k, *k2, *k_pow, *k_pow2, *two, *ln, *base;
  char cn[MAX_DIGITS];
  int n;

  base = create_bigint_from_string(base,"base");;

  n = (l1->length > l2->length) ? l1->length : l2->length;
  itoa(n, cn, 10);

  ln = create_bigint_from_string(base,cn);
  printf("ln became\n");
  bigint_print(ln);
  two = create_bigint_from_string(base "2");

  if(n < 2){
    return bigint_multiply(l1,l2);
  }

  else{
    k = bigint_divide(ln, two);
    k2 = bigint_bit_multiply(k, two);
    k_pow = bigint_power(base, k);
    k_pow2 = bigint_power(base, k2);

    a0 = bigint_modulus(l1, k_pow);
    b0 = bigint_modulus(l2, k_pow);

    a1 = bigint_divide(l1, k_pow);
    b1 = bigint_divide(l2, k_pow);


    c0 = bigint_karasuba(a0, b0);
    c1 = bigint_karasuba(a1, b1);

    c2 = bigint_subtract(bigint_subtract(bigint_bit_multiply(bigint_add(a0,a1), bigint_add(b0,b1)), c0),c1);

    return bigint_add(bigint_add(bigint_bit_multiply(c1, k_pow2), bigint_bit_multiply(c2, k_pow)), c0);
  }

}
