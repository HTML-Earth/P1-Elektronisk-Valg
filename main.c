#include    "encryption.h"
#include    "voting.h"
#define     TRUE 1
#define     FALSE 0

int admin_check(void);
void print_votes(single_vote *dec_votes, int *counted_votes);

int main (int argc, char *argv[]){
    int admin_choice, user_vote, i, candidates, done = 0, admin_mode = 0, counted_votes = 0;
    char string_vote[5], file_name[MAX_CHARS], valgkreds[MAX_CHARS];
    single_vote enc_votes[500], dec_votes[500];
    bigint *enc_vote, *temp_vote;
    stemmeseddel *aalborg_2015;

    aalborg_2015 = (stemmeseddel *)calloc(1,sizeof(stemmeseddel));

    /* If program run with no input-parameters, run voting functions */
    if (argc < 2){
         load_file_info(file_name, valgkreds);
         candidates = check_voting_data(file_name);
         aalborg_2015->kandidater = (kandidat *)calloc(candidates,sizeof(kandidat));
         import_voting_data(aalborg_2015, file_name, valgkreds);
        do{
            user_vote = get_user_vote(aalborg_2015);
            /* if user has chosen to activate admin-function - then we break */
            if(user_vote == 1){
                admin_mode = TRUE;
                done = TRUE;
                break;
            }         

            enc_vote = encryption(user_vote);
            bigint_print_string(string_vote, enc_vote);
            export_enc_vote(string_vote);
        }
        while(!done);       
    }
    else if(strcmp(argv[1], "--admin") == 0){
        admin_mode = TRUE;
    }
 
    /* If admin-mode has been set to true - then we run admin mod with choice to set-file-data or decrypt votes */
    if(admin_mode == TRUE){
        if(admin_check()){
            printf("Press 1 to set vote-data or 2 for decryption of votes\n");
            scanf(" %d", &admin_choice);
            
            if(admin_choice == 2){
              
                import_enc_vote(enc_votes, &counted_votes);

                for (i = 0; i < counted_votes; i++){
                    temp_vote = create_bigint_from_string(enc_votes[i].vote);
                    temp_vote = decryption(temp_vote);
                    bigint_print_string(string_vote, temp_vote);
                    strcpy(dec_votes[i].vote, string_vote);
                }
                print_votes(dec_votes, &counted_votes);
            }
            else if(admin_choice == 1){
                set_file_info();
            }
            else { 
                printf("Input with no function entered - Ending Program\n");
            }
        }
        else{
            printf("Failed admin check - closing program\n");
        }
    }
    
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
            tries = 4;
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


void print_votes(single_vote *dec_votes, int *counted_votes){
    int i;

    for(i = 0; i < *counted_votes; i++){
        printf("Vote: %s\n", dec_votes[i].vote);
    }
}
