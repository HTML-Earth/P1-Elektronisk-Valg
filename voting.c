#include    "encryption.h"
#include    "voting-functions.h"

int main (void){
    int admin_choice, user_vote, i, candidates, done = 0, admin_mode = 0, counted_votes = 0;
    char string_vote[5], file_name[MAX_CHARS], valgkreds[MAX_CHARS];
    single_vote enc_votes[MAX_VOTES], dec_votes[MAX_VOTES];
    bigint *enc_bigint_vote;
    stemmeseddel *kandidat_data;

    do{
        kandidat_data = (stemmeseddel *)calloc(1,sizeof(stemmeseddel));
        load_file_info(file_name, valgkreds);
        candidates = check_voting_data(file_name);

        kandidat_data->kandidater = (kandidat *)calloc(candidates,sizeof(kandidat));
        import_voting_data(kandidat_data, file_name, valgkreds);

        user_vote = get_user_vote(kandidat_data);
      
        if(user_vote == 1){
            done = 1;
            break;
        }
        else{
        enc_bigint_vote = encryption(user_vote);
        bigint_print_string(string_vote, enc_bigint_vote);
        export_enc_vote(string_vote);
        }
    }
    while(!done);
    
    return(0);
}

