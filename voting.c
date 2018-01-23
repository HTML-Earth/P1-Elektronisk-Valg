#include    "encryption.h"
#include    "voting-functions.h"

int main (void){
    int user_vote, candidates, done = 0;
    char string_vote[MAX_CHARS], file_name[MAX_CHARS], valgkreds[MAX_CHARS];
    bigint *enc_bigint_vote;
    stemmeseddel *kandidat_data;

    do{
        /*Load candidate-data for voting*/
        kandidat_data = (stemmeseddel *)calloc(1,sizeof(stemmeseddel));

        if(kandidat_data != NULL){

            load_file_info(file_name, valgkreds);
            candidates = check_voting_data(file_name);

            kandidat_data->kandidater = (kandidat *)calloc(candidates,sizeof(kandidat));

            if(kandidat_data->kandidater != NULL){
                import_voting_data(kandidat_data, file_name, valgkreds);

                user_vote = get_user_vote(kandidat_data);

                /* If sentinel value are given in get_user_vote functions we will break, and exit program */
                if(user_vote == 1){
                    done = 1;
                    break;
                }
                else{
                /*If user_vote is not sentinel value we will encrypt with RSA-encryption*/
                enc_bigint_vote = encryption(user_vote);
                bigint_print_string(string_vote, enc_bigint_vote);
                export_enc_vote(string_vote);
                }

                free(kandidat_data->kandidater);
            }
            else{
                printf("calloc returned NULL pointer\n");
                return (0);
            }
            free(kandidat_data);
        }
        else{
            printf("calloc returned NULL pointer\n");
            return (0);
        }
    }
    while(!done);



    return(0);
}
