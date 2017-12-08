#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

/*Export an encrypted vote to file*/
void export_enc_vote(char *v);

/*Import an encrypted vote to single-vote struct*/
void import_enc_vote(single_vote *dec_votes, int* counted_votes);

/* Choose which file to load candidate-data from - set value of valgkreds */
void set_file_info(void);

/*Get info for which file to use when loading candidate-data */
void load_file_info(char *file_name, char *valgkreds);

/* check how many candidates are in the file - to optimize memory allocation */
int check_voting_data(char *file_name);

/* import candidate-data from speficic file */
void import_voting_data(stemmeseddel *generic_stemmeseddel, char *file_name, char *valgkreds);
