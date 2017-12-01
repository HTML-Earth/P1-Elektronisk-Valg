#include "file-man.h"

void export_vote(char *v){
    FILE *vote_file;

    vote_file = fopen("secretvotes.txt","a");

    fprintf(vote_file, "%s\n",v);
}

void import_vote(all_votes *dec_votes){
    FILE *vote_file;
    char enc_vote[5];
    int i;

    vote_file = fopen("secretvotes.txt","r");

    while(!(feof(vote_file))){  
        fscanf(vote_file, " %s",dec_votes->single_vote[i]);
        i++;
        dec_votes->counted_votes++;
    }
     
    fclose(vote_file);
}
