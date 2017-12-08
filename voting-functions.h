#include <stdio.h>
#include <stdlib.h>
#include "file-man.h"

/* Function for getting a user_vote - prints out candidate-data on stout - scan for user input - return user_vote to calling function */
int get_user_vote(stemmeseddel *generic_stemmeseddel);

/* function for counting decrypted votes - takes a vote and compares with speficic candidate-data */
void count_votes(single_vote *enc_votes, int *counted_votes, stemmeseddel *generic_stemmeseddel);

/* print out all candidates who has recieved at least 1 vote */
void print_voting_result(stemmeseddel *generic_stemmeseddel);
