#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHARS 100

typedef struct{
    char navn[MAX_CHARS];
    int stemmer;
}kandidat; 

typedef struct{
    kandidat *kandidater;
    char valgkreds_navn[MAX_CHARS];
    int antal_kandidater;
    int stemmer;
}stemmeseddel;



int count_file_data(char *file_name);
void load_file_data(stemmeseddel *aalborg_2015);


int main(void){
    int i, data_in_file;
    stemmeseddel *aalborg_2015;
    char *file_name = "stemmeseddel.txt"; 
    aalborg_2015 = (stemmeseddel *)calloc(1,sizeof(stemmeseddel));  
   
    data_in_file = count_file_data(file_name);

    aalborg_2015->kandidater = (kandidat *)calloc(data_in_file, sizeof(kandidat));
    
    load_file_data(aalborg_2015);
    
    printf("Du stemmer i %s\n", aalborg_2015->valgkreds_navn);
    for(i = 0; i < aalborg_2015->antal_kandidater; i++){
        printf("Kandidat %-40s har faaet %3d stemmer\n", aalborg_2015->kandidater[i].navn, aalborg_2015->kandidater[i].stemmer);
    }   

    return 0;
}

int count_file_data(char *file_name){
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

void load_file_data(stemmeseddel *aalborg_2015){

    FILE *fp;
    int  i = 0;   

    strcpy(aalborg_2015->valgkreds_navn,"Aalborg Valgkreds");

    fp = fopen("stemmeseddel.txt", "r");
     

    if (fp != NULL){
        while(!(feof(fp))){
            fscanf(fp, " %[abcdefghijklmnopqrstuvwxzyABCDEFGHIJKLMNOPQRSTUVWXZY.- ]:", aalborg_2015->kandidater[i].navn);
            i++;
            aalborg_2015->antal_kandidater += 1;      
        }
    }
    fclose(fp);
}

    

