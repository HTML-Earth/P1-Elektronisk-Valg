#include <stdio.h>
#include "bigints.h"

#define CHARLENGTH 10
#define MAX_VOTES 1000

void get_vote(char *v);
bigint *encryption(int v);
bigint *decryption(bigint *c);
