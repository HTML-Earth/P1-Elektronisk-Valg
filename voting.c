#include    "bigints.h"
#include    "encryption.h"
#include    "decryption.h"

int vote_counting(int decrypted_vote);
int vote_decrypt(int decrypted_vote);
int voting_function(void);
int vote_or_decrypt(int decrypted_vote);
void check(char *pin);

int main (void){
    int decrypted_vote;
    char *pin[12]

    decrypted_vote=vote_or_decrypt;

    if(decrypted_vote==-1)
        printf("ERROR!\n");
    else if(decrypted_vote==-10){
        printf("Please enter your Randomly generated pin.\n")
        scanf("%s\n",pin);
        check(pin);
    }
    else
    encryption(decrypted_vote);

    return(0);
}

/*
This function gives the user the option to choose between voting or decrypting an already encrypted vote.
And when either option is choosen, it goes to it's own function.
*/

int vote_or_decrypt(void){

    char user_choice[6];
    int  vote;

    printf("Would you like to 'vote' or 'decrypt' votes?:    ");
    if (scanf("%s", &user_choice) != 1){
        printf("Invalid input!\n");
        return(-1);
    }
    if (strcmp(user_choice, "vote") == 0 || strcmp(user_choice, "Vote") == 0){
        printf("You have chosen to vote\n");
        vote = voting_function();
    }
    else if (strcmp(user_choice, "decrypt") == 0 || strcmp(user_choice, "Decrypt") == 0){
        printf("You have chosen to count exisiting votes\n");
        return -10;
    }
    else{
        printf("Invalid input!\n");
        return(-1);
    }

    return vote;
}

/*
This function handles the voting in itself. It gives the option to choose between the 10 politcal parties of Denmark plus an option to vote blank.
*/
int voting_function(void){

    int     user_input = 0;
    char    user_confirmation[4];

    printf("[0]    (0) Blank\n");
    printf("[1]    (A) Socialdemokraterne\n");
    printf("[2]    (B) Radikale Venstre\n");
    printf("[3]    (C) Det Konservative Folkeparti\n");
    printf("[4]    (F) Socialistisk Folkeparti\n");
    printf("[5]    (I) Liberal Alliance\n");
    printf("[6]    (K) Kristendemokraterne\n");
    printf("[7]    (O) Dansk Folkeparti\n");
    printf("[8]    (V) Venstre\n");
    printf("[9]    (OE) Enhedslisten\n");
    printf("[10]   (AA) Alternativet\n");
    printf("Input the number representing the party you would like to vote for:    ");

    if (scanf("%d", &user_input) != 1){
        printf("Invalid input!\n");
        return(-1);
    }
    if (user_input < 0 || user_input > 10){
        printf("User input must be between 0 and 10\n");
        return(-1);
    }

    switch(user_input){
        case 1 :
            printf("Do you wish to vote for (A) Socialdemokraterne?\n");
            break;
        case 2 :
            printf("Do you wish to vote for (B) Radikale Venstre?\n");
            break;
        case 3 :
            printf("Do you wish to vote for (C) Det Konservative Folkeparti?\n");
            break;
        case 4 :
            printf("Do you wish to vote for (F) Socilistisk Folkeparti?\n");
            break;
        case 5 :
            printf("Do you wish to vote for (I) Liberal Alliance?\n");
            break;
        case 6 :
            printf("Do you wish to vote for (K) Kristendemokraterne?\n");
            break;
        case 7 :
            printf("Do you wish to vote for (O) Dansk Folkeparti?\n");
            break;
        case 8 :
            printf("Do you wish to vote for (V) Venstre?\n");
            break;
        case 9 :
            printf("Do you wish to vote for (OE) Enhedslisten\n");
            break;
        case 10 :
            printf("Do you wish to vote for (AA) Alternativet\n");
            break;
        default :
            printf("Do you wish to vote blank?\n");

    }
    	/*
    	Asks for confirmation
    	*/
        printf("'Yes' / 'No' ?\n");

        if (scanf("%s", user_confirmation) != 1){
            printf("Invalid input!");
            return (-1);
        }
            if (strcmp(user_confirmation, "Yes") == 0 || strcmp(user_confirmation, "yes") == 0){
                printf("Vote registered\n");
            }

        else{
            printf("Voting resetting\n");
            voting_function();
        }


    return user_input;
}

void check(char *pin){
    char *pincheck;
    FILE *pinregistry;

    pinregistry=fopen("pin.txt","r");

    fscanf("%s",pincheck);

    if(strcmp(pincheck,pin)==0)
        decryption();

    else
        printf("Error");
}

/*
Now that the user confirmed his input, we send the vote to the corresponding party
*/
/*int    vote_counting(int decrypted_vote){

    char    party_voted_on[50], filename[50];
    FILE    *vote_count_file;
    int     votes_already = 0;

    switch(decrypted_vote){

        case 1 :
            strcpy(party_voted_on, "Socialdemokraterne");
            break;
        case 2 :
            strcpy(party_voted_on, "Radikale_Venstre");
            break;
        case 3 :
            strcpy(party_voted_on, "Det_Konservative_Folkeparti");
            break;
        case 4 :
            strcpy(party_voted_on, "Socalistisk_Folkeparti");
            break;
        case 5 :
            strcpy(party_voted_on, "Liberal_Alliance");
            break;
        case 6 :
            strcpy(party_voted_on, "Kristendemokraterne");
            break;
        case 7 :
            strcpy(party_voted_on, "Dansk_Folkeparti");
            break;
        case 8 :
            strcpy(party_voted_on, "Venstre");
            break;
        case 9 :
            strcpy(party_voted_on, "Enhedslisten");
            break;
        case 10 :
            strcpy(party_voted_on, "Alternativet");
            break;
        default :
            strcpy(party_voted_on, "Blank_votes");
    }

    sprintf(filename, "%s.txt", party_voted_on);

    if (access (filename, F_OK) != -1){
        vote_count_file = fopen(filename, "r");
        fscanf(vote_count_file, "%d\n", &votes_already);
        fclose(vote_count_file);
        vote_count_file = fopen(filename, "w+");
        votes_already++;
        rewind(vote_count_file);
        fprintf(vote_count_file, "%d\n", votes_already);
        fclose(vote_count_file);
    }
    else{
        vote_count_file = fopen(filename, "w+");
        rewind(vote_count_file);
        fprintf(vote_count_file, "1\n");
        fclose(vote_count_file);
    }


    return(0);
}*/

/*
Here the user can decrypt his own vote to make sure it was counted right
*/
/*int vote_decrypt(int decrypted_vote){

	printf("What is your encrypted vote?\n");

    switch(scanf("%f", &decrypted_vote)){

        case 1 :
            printf("Your vote was registered for (A) Socialdemokraterne?\n");
            break;
        case 2 :
            printf("Your vote was registered for (B) Radikale Venstre?\n");
            break;
        case 3 :
            printf("Your vote was registered for (C) Det Konservative Folkeparti?\n");
            break;
        case 4 :
            printf("Your vote was registered for (F) Socilistisk Folkeparti?\n");
            break;
        case 5 :
            printf("Your vote was registered for (I) Liberal Alliance?\n");
            break;
        case 6 :
            printf("Your vote was registered for (K) Kristendemokraterne?\n");
            break;
        case 7 :
            printf("Your vote was registered for (O) Dansk Folkeparti?\n");
            break;
        case 8 :
            printf("Your vote was registered for (V) Venstre?\n");
            break;
        case 9 :
            printf("Your vote was registered for (OE) Enhedslisten\n");
            break;
        case 10 :
            printf("Your vote was registered for (AA) Alternativet\n");
            break;
        default :
            printf("No vote to decrypt found\n");
    }

    return(0);
}
*/
