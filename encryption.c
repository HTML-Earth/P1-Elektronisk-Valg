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

/* Gets the vote from user and stores in v-variable */
void get_vote(char *v){

    printf("Enter a positive integer below 20, as a symbol for a vote\n");
    scanf(" %s", v);
}

/* takes vote from main - Encrypts using RSA-encryption algorithm - returns encrypted vote to c-variable in main */
bigint *encryption(int v){
    bigint *e, *n, *bv;
    char nstring[CHARLENGTH], estring[CHARLENGTH], vote[CHARLENGTH];
    FILE *value;

    /* create a string and bigint from vote value */
    sprintf(vote, "%d", v);
    bv = create_bigint_from_string(vote);

    value = fopen("encryption_values.txt","r");

    fscanf(value," N=%s E=%s",nstring, estring);

    fclose(value);

    /* Values for primnumbers p1 & p2, along with correct values for e & d, are chosen and calculated before-hand using the algorythms described in RSA-chapter in the report */

    e = create_bigint_from_string(estring);
    n = create_bigint_from_string(nstring);

    return bigint_modulus(bigint_pow(bv, e), n);
}

/* takes encrypted vote from main along with needed values for d & n - decrypts vote using RSA-algorithm - returns decrypted vote to dec_vote variable in main */
bigint *decryption(bigint *c){
    bigint *n, *d;
    char nstring[CHARLENGTH], dstring[CHARLENGTH];
    FILE *value;

    value = fopen("decryption_values.txt","r");

    fscanf(value," N=%s D=%s",nstring, dstring);

    fclose(value);

    d = create_bigint_from_string(dstring);
    n = create_bigint_from_string(nstring);


    return bigint_modulus(bigint_pow(c, d ), n);
}
