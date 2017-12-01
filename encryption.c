#include "encryption.h"

int main(void){
    FILE *votes;
    bigint v, c;
    char vote[CHARLENGTH];
    int i;


    votes = fopen("secretvotes.txt","a");

    get_vote(vote);
    v = create_bigint_from_string(vote);
    c = encrypt_vote(v);

    fprintf(votes,"\n");
    for (i = c.length - 1; i >= 0; i--) {
        printf("%d", c.digits[i]);
        fprintf(votes,"%d",c.digits[i]);
    }
    printf("\n");
    fclose(votes);

    return 0;
}

/* Gets the vote from user and stores in v-variable */
void get_vote(char *v){

    printf("Enter a positive integer below 20, as a symbol for a vote\n");
    scanf(" %s", v);
}

/* takes vote from main - Encrypts using RSA-encryption algorithm - returns encrypted vote to c-variable in main */
bigint encryption(int v){
    bigint e, n, bv;
    char nstring[CHARLENGTH], estring[CHARLENGTH], vote[CHARLENGTH];
    FILE *value;
  
    sprintf(vote, %d, v);
    bv = create_bigint_from_string(vote);

    value = fopen("superhemmeligvalues","r");

    fscanf(value," N=%s",nstring);
    fscanf(value," E=%s",estring);


    fclose(value);

    /* Values for primnumbers p1 & p2, along with correct values for e & d, are chosen and calculated before-hand using the algorythms described in RSA-chapter in the report */

    e = create_bigint_from_string(estring);
    n = create_bigint_from_string(nstring);

    return bigint_modulus(bigint_pow(v, e), n);
}
