#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void export_vote(char *v);
void import_vote(single_vote *dec_votes, int* counted_votes);
int check_voting_data(char *file_name);
void import_voting_data(stemmeseddel *generic_stemmeseddel, char *file_name, char *valgkreds);
