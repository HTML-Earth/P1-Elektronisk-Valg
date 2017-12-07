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
    bigint *e, *n, *bv, *i, *c, *one;
    char nstring[CHARLENGTH], estring[CHARLENGTH], vote[CHARLENGTH];
    FILE *value;

    /* create a string and bigint from vote value */
    sprintf(vote, "%d", v);
    bv = create_bigint_from_string(10, vote);

    value = fopen("encryption_values.txt","r");

    fscanf(value," N=%s E=%s",nstring, estring);

    fclose(value);

    /* Values for primnumbers p1 & p2, along with correct values for e & d, are chosen and calculated before-hand using the algorythms described in RSA-chapter in the report */
    i = create_bigint_from_string(10, "0");
    e = create_bigint_from_string(10, estring);
    n = create_bigint_from_string(10, nstring);
    c = create_bigint_from_string(10, "1");
    one = create_bigint_from_string(10, "1");
    
    while(bigint_compare(i, e) == -1){
           c = bigint_modulus(bigint_multiply(c, bv), n); 
           i = bigint_add(i, one);
       }
    return c;
    
    /*return bigint_modulus(bigint_pow(bv, e), n);*/
}

/* takes encrypted vote from main along with needed values for d & n - decrypts vote using RSA-algorithm - returns decrypted vote to dec_vote variable in main */
bigint *decryption(bigint *c){
    bigint *n, *d, *two, *one, *nc, *i;
    char nstring[CHARLENGTH], dstring[CHARLENGTH];
    FILE *value;

    value = fopen("decryption_values.txt","r");

    fscanf(value," N=%s D=%s",nstring, dstring);

    fclose(value);

    i = create_bigint_from_string(10, "0");
    nc = create_bigint_from_string(10, "1");
    one = create_bigint_from_string(10, "1");
    d = create_bigint_from_string(10, dstring);
    n = create_bigint_from_string(10, nstring); 
    two = create_bigint_from_string(10, "2");

    
    while(bigint_compare(i, d) == -1){
           nc = bigint_modulus(bigint_multiply(nc, c), n); 
           i = bigint_add(i, one);
       }
    return bigint_subtract(nc, two);

/*    return bigint_subtract(bigint_modulus(bigint_pow(c, d ), n),two); */
}
