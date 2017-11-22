/* dette er et udkast til en krypteringsfunktion der benytter sig af RSA-kryptering ved de nuværende INT-datatyper i C, og kryptere et enkelt heltal */
#include <stdio.h>

void get_vote(unsigned long *m);
unsigned long encrypt_vote(unsigned long v, unsigned long *d, unsigned long *n);
unsigned long exp_func(unsigned long v, unsigned long e);
unsigned long decrypt_vote(unsigned long c, unsigned long d, unsigned long n);

int main(void){
	FILE *votes;
    unsigned long v, c, d, n, dec_vote;

	votes = fopen("secretvotes.txt","w");
    get_vote(&v);
    c = encrypt_vote(v, &d, &n);
    printf("The encrypted vote is: %lu\n", c);	
	fprintf(votes,"%lu",c);
	fclose(votes);
	
    dec_vote = decrypt_vote(c, d, n);
    printf("The decrypted vote is: %lu\n", dec_vote);


    return 0;
}

/* Gets the vote from user and stores in v-variable */
void get_vote(unsigned long *v){

    printf("Enter a positive integer below 20, as a symbol for a vote\n");
    scanf(" %lu", v);
}

/* takes vote from main - Encrypts using RSA-encryption algorithm - returns encrypted vote to c-variable in main */
unsigned long encrypt_vote(unsigned long v, unsigned long *d, unsigned long *n){
    unsigned long p1, p2, e;

    /* Values for primnumbers p1 & p2, along with correct values for e & d, are chosen and calculated before-hand using the algorythms described in RSA-chapter in the report */
    p1 = 3;
    p2 = 11;
    
    e = 7;
    *d = 3;
    *n = p1 * p2;

    return exp_func(v,e) % *n;
}

/* takes encrypted vote from main along with needed values for d & n - decrypts vote using RSA-algorithm - returns decrypted vote to dec_vote variable in main */
unsigned long decrypt_vote(unsigned long c, unsigned long d, unsigned long n){

    return exp_func(c,d) % n;
}

/* takes a number and a value for exponent - multiplies the given number with itself as many times as the exponent indicates */
unsigned long exp_func(unsigned long v, unsigned long exp){
    int i;
    unsigned long result = v;

    for (i = 1; i < exp; i++){
        result = result * v; 
    }
    return result;
}
    
    

