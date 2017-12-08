#include "encryption.h"

/* DECRYPTION OLD MAIN

int main(void){
    FILE *votes;
    char vote[5];
    bigint c, dec_vote;
    int control, i;

    votes = fopen("secretvotes.txt","r");

    while ((control = fgetc(votes)) != EOF){
        fscanf(votes, " %s", vote);
        c = create_bigint_from_string(vote);
        dec_vote = decrypt_vote(c);

        for (i = dec_vote.length - 1; i >= 0; i--) {
            printf("%d", dec_vote.digits[i]);
        };
        printf("\n");
    }
    fclose(votes);

    return 0;
}
*/


/* takes vote from main - Encrypts using RSA-encryption algorithm - returns encrypted vote to c-variable in main */
bigint *encryption(int v){
    bigint *e, *n, *bv, *c;
    char nstring[CHARLENGTH], estring[CHARLENGTH], vote[CHARLENGTH];
    FILE *value;

    /* create a string and bigint from vote value */
    sprintf(vote, "%d", v);
    bv = create_bigint_from_string(10, vote);

    value = fopen("encryption_values.txt","r");

    fscanf(value," N=%s E=%s",nstring, estring);

    fclose(value);

    /* Values for primnumbers p1 & p2, along with correct values for e & d, are chosen and calculated before-hand using the algorythms described in RSA-chapter in the report */

    e = create_bigint_from_string(10, estring);
    n = create_bigint_from_string(10, nstring);


    return generic_algo(bv, e, n);

    /*return bigint_modulus(bigint_pow(bv, e), n);*/
}

/* takes encrypted vote from main along with needed values for d & n - decrypts vote using RSA-algorithm - returns decrypted vote to dec_vote variable in main */
bigint *decryption(bigint *c){
    bigint *n, *d, *two;
    char nstring[CHARLENGTH], dstring[CHARLENGTH];
    FILE *value;

    value = fopen("decryption_values.txt","r");

    fscanf(value," N=%s D=%s",nstring, dstring);

    fclose(value);
    d = create_bigint_from_string(10, dstring);
    n = create_bigint_from_string(10, nstring);
    two = create_bigint_from_string(10, "2");


    return generic_algo(c,d,n);

/*    return bigint_subtract(bigint_modulus(bigint_pow(c, d ), n),two); */
}

bigint *generic_algo(bigint *v, bigint *pow_v, bigint *mod_v){
    bigint *c, *one, *temp_v, *temp_pow_v, *temp_mod_v;
    int *counters;
    int i;

/*
      temp_v = bigint_convert_base(v, 256, 2, 5, 6);
      printf("\nconvert done\n");
      temp_pow_v = bigint_convert_base(pow_v, 256, 2, 5, 6);
      printf("convert done\n");
      temp_mod_v = bigint_convert_base(mod_v, 256, 2, 5, 6);
      printf("convert done\n");
      */
      counters = (int *)calloc(pow_v->length, sizeof(int));

      i = create_bigint_from_string(10, "0");
      c = create_bigint_from_string(10, "1");
      one = create_bigint_from_string(10, "1");


      for(i = 0; i < pow_v->length; i++) {
          for(counters[i] = 0; counters[i] < pow_v->digits[i] * custom_pow(10,i); counters[i]++) {
              c = bigint_modulus(bigint_multiply(c, v), mod_v);
          }
      }
      /*
      while(bigint_compare(i, pow_v) == -1){
             c = bigint_modulus(bigint_multiply(c, v), mod_v);
             i = bigint_add(i, one);
      }
      */
      return c;
  }
