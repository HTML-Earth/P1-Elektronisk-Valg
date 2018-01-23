#include    "encryption.h"
#include    "voting-functions.h"

#define TRUE 1
#define FALSE 0

int admin_check(void);

int main (void){
    int admin_choice, i, candidates, counted_votes = 0;
    char string_vote[5], file_name[MAX_CHARS], valgkreds[MAX_CHARS];
    single_vote enc_votes[MAX_VOTES], dec_votes[MAX_VOTES];
    bigint *temp_bigint_vote;
    stemmeseddel *kandidat_data;

    /* Make admin check to ensure only trusted person can gain access to decryption */
    if(admin_check()){
        printf("Press 1 to set vote-data or 2 for decryption of votes, or press other number to exit program\n");
        scanf(" %d", &admin_choice);

        if(admin_choice == 1){
            set_file_info();
        }
        else if(admin_choice == 2){
            import_enc_vote(enc_votes, &counted_votes);

            /*Encrypted votes are strings - convert to bigint before decryption - after we copy our decrypted vote to struct of single votes */
            for (i = 0; i < counted_votes; i++){
                temp_bigint_vote = create_bigint_from_string(10,enc_votes[i].vote);
                temp_bigint_vote = decryption(temp_bigint_vote);
                bigint_print_string(string_vote, temp_bigint_vote);
                strcpy(dec_votes[i].vote, string_vote);
            }
            printf("Votes have been decrypted - Do you wish to count votes for each candidate press 1 - press other number to exit program\n");
            scanf(" %d", &admin_choice);

            if(admin_choice == 1){
                /* If we want to count votes, we must first collect candidate data, to compare with our decrypted votes that are int-values */
                kandidat_data = (stemmeseddel *)calloc(1,sizeof(stemmeseddel));

                if(kandidat_data != NULL){
                    load_file_info(file_name, valgkreds);
                    candidates = check_voting_data(file_name);

                    kandidat_data->kandidater = (kandidat *)calloc(candidates,sizeof(kandidat));

                    if(kandidat_data->kandidater != NULL){
                        import_voting_data(kandidat_data, file_name, valgkreds);

                        count_votes(dec_votes, &counted_votes, kandidat_data);
                        print_voting_result(kandidat_data);
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
            else printf("Exiting program\n");
        }
        else printf("Input with no function entered - Ending Program\n");
    }
    else printf("Failed admin check - closing program\n");

    return(0);
}

/* checks if admin-pin is entered - maximum 3 tries - if wrong then exit program */
int admin_check(void){
    char pincheck[12], pin[12];
    FILE *pinregistry;
    int check, tries = 0;

    pinregistry = fopen("pin.txt","r");

    fscanf(pinregistry, "%s", pincheck);

    fclose(pinregistry);

    do{

        printf("Please enter your admin pin.\n");
        scanf("%s",pin);

        if(strcmp(pincheck , pin) ==0){
            check = TRUE;
            tries = 3;
        }

        else {
            check = FALSE;
            printf("Wrong pin - try again\n");
        }
        tries++;
    }
    while(tries < 3);
    return check;
}
