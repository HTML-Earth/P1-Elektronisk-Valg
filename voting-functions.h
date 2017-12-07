#include <stdio.h>
#include <stdlib.h>
#include "file-man.h"

int get_user_vote(stemmeseddel *generic_stemmeseddel);
void count_votes(single_vote *enc_votes, int *counted_votes, stemmeseddel *generic_stemmeseddel);
void print_voting_result(stemmeseddel *generic_stemmeseddel);
