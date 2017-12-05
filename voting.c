#include "voting.h"

int get_user_vote(stemmeseddel *generic_stemmeseddel){
    int i, user_vote, temp, l_choice, done, enc_add = 2;
    
    do{
        printf("Du stemmer i valgkreds %s\nDu har nu foelgende kandidater at stemme paa\n\n", generic_stemmeseddel->valgkreds_navn);
    
        for(i = 0; i < generic_stemmeseddel->antal_kandidater; i++){
            printf("Kandidat %-40s - Tast %5d\n", generic_stemmeseddel->kandidater[i].navn, i);
        }

        scanf(" %d", &temp);

        if((temp < 0) || (temp > generic_stemmeseddel->antal_kandidater-1)){
            printf("Du har indtastet et forkert nummer - Proev igen\n");
            done = 0;
        }

        else if(temp == -1){
            printf("Do you wish to enter admin-mode - if yes enter -1, else enter 0 to start voting-program again\n");
            scanf(" %d", &temp);
            if(temp == -1){
                done = 1;
                user_vote = temp;
                printf("Entering admin-mode\n");
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
    while(!done);

    return user_vote+enc_add;
}
  

    

