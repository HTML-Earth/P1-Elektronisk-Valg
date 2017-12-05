#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file-man.h"

int main(void){
    int i, data_in_file;
    stemmeseddel *aalborg_2015;
    char file_name[MAX_CHARS];
    char valgkreds[MAX_CHARS];

    printf("Enter Valgkreds:\n");
    scanf(" %s", valgkreds);
    printf("Enter file name\n");
    scanf(" %s", file_name);   


    aalborg_2015 = (stemmeseddel *)calloc(1,sizeof(stemmeseddel));  
   
    data_in_file = check_voting_data(file_name);

    aalborg_2015->kandidater = (kandidat *)calloc(data_in_file, sizeof(kandidat));
    
    import_voting_data(aalborg_2015, file_name, valgkreds);
    
    printf("Du stemmer i %s\n", aalborg_2015->valgkreds_navn);
    for(i = 0; i < aalborg_2015->antal_kandidater; i++){
        printf("Kandidat %-40s har faaet %3d stemmer\n", aalborg_2015->kandidater[i].navn, aalborg_2015->kandidater[i].stemmer);
    }   

    return 0;
}
