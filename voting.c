#include    <stdio.h>
#include    <string.h>


int vote_counting(int decrypted_vote);
int vote_decrypt(void);
int voting_function(void);
int vote_or_decrypt(void);

int main (void){

    vote_or_decrypt(decrypted_vote);
    /* this is the function to call when the vote has been encrypted and decrypted
       this function will then assign the vote to the corresponding party*/
    vote_counting(decrypted_vote);

    return(0);
}

/*
This function gives the user the option to choose between voting or decrypting an already encrypted vote.
And when either option is choosen, it goes to it's own function.
*/

int vote_or_decrypt(int decrypted_vote){

    char user_choice[6];
    int  vote;

    printf("Would you like to 'vote' or 'check' an existing vote?:    ");
    if (scanf("%s", &user_choice) != 1){
        printf("Invalid input!\n");
        return(1);
    }
    if (strcmp(user_choice, "vote") == 0 || strcmp(user_choice, "Vote") == 0){
        printf("You have chosen to vote\n");
        vote = voting_function();
    }
    else if (strcmp(user_choice, "check") == 0 || strcmp(user_choice, "Check") == 0){
        printf("You have chosen to check an exisiting vote\n");
        vote_decrypt(decrypted_vote);
    }
    else{
        printf("Invalid input!\n");
        return(1);
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
        return(1);
    }
    if (user_input < 0 || user_input > 10){
        printf("User input must be between 0 and 10\n");
        return(1);
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

        printf("'Yes' / 'No' ?\n");

        if (scanf("%s", user_confirmation) != 1){
            printf("Invalid input!");
            return(0);
        }
            if (strcmp(user_confirmation, "Yes") == 0 || strcmp(user_confirmation, "yes") == 0){
                printf("Vote registered\n");
                return user_input;
            }

        else{
            printf("Voting cancelled\n");
            return(0);
        }


    return(0);
}

/*
Now that the user confirmed his input, we send the vote to the corresponding party
*/
int    vote_counting(int decrypted_vote){

    switch(decrypted_vote){

        case 1 :
            break;
        case 2 :
            break;
        case 3 :
            break;
        case 4 :
            break;
        case 5 :
            break;
        case 6 :
            break;
        case 7 :
            break;
        case 8 :
            break;
        case 9 :
            break;
        case 10 :
            break;
        default :
    }

    return(0);
}

/*
Here the user can decrypt his own vote to make sure it was counted right
*/
int vote_decrypt(int decrypted_vote){

    switch(decrypted_vote){

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
            printf("Do you wish to vote blank?\n");
    }

    return(0);
}
