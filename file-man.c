#include "file-man.h"
#include <string.h>

void export_enc_vote(char *v){
    FILE *fp;

    fp = fopen("secretvotes.txt","a");

    fprintf(fp, " %s",v);
	fprintf(fp, "\n",v);
	
	fclose(fp);
}

void import_enc_vote(single_vote *dec_votes, int *counted_votes){
    FILE *fp;
    int i = 0, control, scanres = 0;

    fp = fopen("secretvotes.txt","r");
    if(fp != NULL){
        while((control = fgetc(fp)) != EOF ){
            scanres = fscanf(fp, " %[0123456789]", dec_votes[i].vote);
            i++;
	    if(scanres == 1){
	        *counted_votes += 1;
	    }
        }
    }
    fclose(fp);
}

void set_file_info(void){
    FILE *fp;
    char file_name[MAX_CHARS], valgkreds[MAX_CHARS];

    fp = fopen("voting-info.txt", "w");
    if (fp != NULL){
        printf("Enter Valgkreds:\n");
        scanf(" %s", valgkreds);
        printf("Enter file name\n");
        scanf(" %s", file_name); 

        fprintf(fp, "%s\n%s\n", file_name, valgkreds); 
    }
    fclose(fp);
    printf("File info has been set - Thank you\n");
}


void load_file_info(char *file_name, char *valgkreds){
    FILE *fp;
  
    fp = fopen("voting-info.txt", "r");
  
    if (fp != NULL){
        fscanf(fp, " %s %s", file_name, valgkreds);
    }
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
  
