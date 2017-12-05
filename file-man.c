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

int check_voting_data(char *file_name){

    int scan_control, file_lines = 1;
    FILE *fp;

    fp = fopen(file_name, "r");
    if (fp != NULL){
      while((scan_control = fgetc(fp))  != EOF){
        if (scan_control == '\n'){
          file_lines++;
        }
      }
    }
    fclose(fp);
    return file_lines;
}

  
void import_voting_data(stemmeseddel *generic_stemmeseddel, char *file_name, char *valgkreds){

    FILE *fp;
    int  i = 0;   

    strcpy(generic_stemmeseddel->valgkreds_navn, valgkreds);

    fp = fopen(file_name, "r");
     

    if (fp != NULL){
        while(!(feof(fp))){
            fscanf(fp, " %[abcdefghijklmnopqrstuvwxzyABCDEFGHIJKLMNOPQRSTUVWXZY.- ]:", generic_stemmeseddel->kandidater[i].navn);
            i++;
            generic_stemmeseddel->antal_kandidater += 1;      
        }
    }
    fclose(fp);
}
  
