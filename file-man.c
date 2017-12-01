#include "file-man.h"

void export_vote(char *v){
    FILE *vote_file;

    vote_file = fopen("secretvotes.txt","a");

    fprintf(vote_file, " %s",v);
	fprintf(vote_file, "\n",v);
}

void import_vote(single_vote *dec_votes, int *counted_votes){
    FILE *vote_file;
    int i = 0, control, scanres = 0;

    vote_file = fopen("secretvotes.txt","r");
	if(vote_file != NULL){
	    while((control = fgetc(vote_file)) != EOF ){
        scanres = fscanf(vote_file, " %[0123456789]", dec_votes[i].vote);
        i++;
		    if(scanres == 1){
		        *counted_votes += 1;
		    }
		}
    }
    fclose(vote_file);
}
