#include "voting-functions.h"

int get_user_vote(stemmeseddel *generic_stemmeseddel){
    int i, user_vote, temp, l_choice, done = 0, enc_add = 2;
    
     while(!done){
        printf("Velkommen.\nDu stemmer i valgkreds %s\nDu har nu foelgende kandidater at stemme paa\n\n", generic_stemmeseddel->valgkreds_navn);
    
        for(i = 0; i < generic_stemmeseddel->antal_kandidater; i++){
            printf("%-5d %-40s\n", i, generic_stemmeseddel->kandidater[i].navn);
        }

        scanf(" %d", &temp);

        if((temp < -1) || (temp > generic_stemmeseddel->antal_kandidater)){
            printf("Du har indtastet et forkert nummer - Proev igen\n");
            done = 0;
        }

        else if(temp == -1){
            printf("Do you wish to exit program - if yes enter -1, else enter 0 to start voting-program again\n");
            scanf(" %d", &temp);
            if(temp == -1){
                done = 1;
                user_vote = temp;
                printf("Exiting - program\n");
            }
            else{
                done = 0;
            }
        }
        else{
            printf("Du har indtastet %d, for at stemme paa %s\nEr dette korrekt? tast 1 - Ellers tast vilkaarligt for at proeve igen\n", temp, generic_stemmeseddel->kandidater[temp].navn);
            scanf(" %d", &l_choice);
    
            if(l_choice == 1){
                user_vote = temp;
                generic_stemmeseddel->kandidater[temp].stemmer += 1;
                done = 1;
            }
            else{
                done = 0;
            }
        }
    }

    return user_vote+enc_add;
}
 
void count_votes(single_vote *enc_votes, int *counted_votes, stemmeseddel *generic_stemmeseddel){

    int i, j, temp_cmp;

    for(i = 0; i < generic_stemmeseddel->antal_kandidater; i++){
        for(j = 0; j < *counted_votes; j++){
            temp_cmp = atoi(enc_votes[j].vote);
            if(i == temp_cmp){
                generic_stemmeseddel->kandidater[i].stemmer += 1;
            }
        }
    }
}

void print_voting_result(stemmeseddel *gs){
   
    int i;
    printf("%-40s %-15s\n", "Kandidat", "Antal stemmer");
    for(i = 0; i < gs->antal_kandidater; i++){
        if(gs->kandidater[i].stemmer > 0){
            printf("%-40s %-5d\n", gs->kandidater[i].navn, gs->kandidater[i].stemmer);
        }
    }
}
   

        

