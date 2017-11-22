/* dette er et udkast til en krypteringsfunktion der benytter sig af RSA-kryptering ved de nuværende INT-datatyper i C, og kryptere et enkelt heltal */
#include <stdio.h>

unsigned long exp_func(unsigned long v, unsigned long e);
unsigned long decrypt_vote(unsigned long c);

int main(void){
    FILE *votes;
    unsigned long c, dec_vote;

    votes = fopen("secretvotes.txt","r");
    fscanf(votes, " %lu", &c);	
    dec_vote = decrypt_vote(c);
    printf("The decrypted vote is: %lu\n", dec_vote);

    return 0;
}

/* takes encrypted vote from main along with needed values for d & n - decrypts vote using RSA-algorithm - returns decrypted vote to dec_vote variable in main */
unsigned long decrypt_vote(unsigned long c){
    unsigned long p1, p2, n, d;
    p1 = 3;
    p2 = 11;

    d = 3;
    n = p1 * p2;

    return exp_func(c,d) % n;
}

/* takes a number and a value for exponent - multiplies the given number with itself as many times as the exponent indicates */
unsigned long exp_func(unsigned long c, unsigned long exp){
    int i;
    unsigned long result = c;

    for (i = 1; i < exp; i++){
        result = result * c; 
    }
    return result;
}
    
    

