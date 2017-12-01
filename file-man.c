#include "file-man.h"

void export_vote(char *v){
    FILE *vote_file;

    vote_file = fopen("secretvotes.txt","a");

    fprintf(vote_file, "%s\n",v);
}

void import_vote(single_vote *dec_votes){
    FILE *vote_file;
    int i;

    vote_file = fopen("secretvotes.txt","r");

    while(!(feof(vote_file))){
        fscanf(vote_file, " %s",dec_votes[i].vote);
        i++;
    }

    fclose(vote_file);
}
