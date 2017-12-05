#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void export_enc_vote(char *v);
void import_enc_vote(single_vote *dec_votes, int* counted_votes);
void set_file_info(void);
void load_file_info(char *file_name, char *valgkreds);
int check_voting_data(char *file_name);
void import_voting_data(stemmeseddel *generic_stemmeseddel, char *file_name, char *valgkreds);
