#include <stdio.h>
#include "bigints.h"

#define CHARLENGTH 10
#define MAX_VOTES 50

/* old function for getting user vote*/
void get_vote(char *v);

/* encrypt-function that uses RSA algorithms */
bigint *encryption(int v);

/* encrypt-function that uses RSA algorithms */
bigint *decryption(bigint *c);

/* function that uses generic encryption algorithm */
bigint *generic_algo(bigint *v, bigint *pow_v, bigint *mod_v);
