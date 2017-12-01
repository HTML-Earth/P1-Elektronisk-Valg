#include "decryption.h"

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

/* takes encrypted vote from main along with needed values for d & n - decrypts vote using RSA-algorithm - returns decrypted vote to dec_vote variable in main */
bigint decryption(bigint c){
    bigint p1, p2, n, d;
    p1 = create_bigint_from_string("3");
    p2 = create_bigint_from_string("11");

    d = create_bigint_from_string("3");
    n = bigint_multiply(p1, p2);

    return bigint_modulus(bigint_pow(c, d ), n);
}
