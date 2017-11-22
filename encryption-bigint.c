/* dette er et udkast til en krypteringsfunktion der benytter sig af RSA-kryptering ved de nuv�rende INT-datatyper i C, og kryptere et enkelt heltal */
#include <stdio.h>
#include "bigints.h"

void get_vote(char *v);
bigint encrypt_vote(bigint v);

int main(void){
    FILE *votes;
    bigint v, c;
    char vote[5];
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
bigint encrypt_vote(bigint v){
    bigint p1, p2, e, n;

    /* Values for primnumbers p1 & p2, along with correct values for e & d, are chosen and calculated before-hand using the algorythms described in RSA-chapter in the report */
    p1 = create_bigint_from_string("3");
    p2 = create_bigint_from_string("11");
    
    e = create_bigint_from_string("7");
    n = bigint_multiply(p1, p2);

    return bigint_modulus(bigint_pow(v, e), n);
}
    
