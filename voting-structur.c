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
    char navn[MAX_CHARS];
    int antal_kandidater;
    int stemmer;
}parti;

typedef struct{
    parti *partier;
}stemmeseddel;

typedef struct{
    kandidat *temp_kan;
    int total_loaded;
    int total_parties;    
}all;

int count_file_data(void);
void load_file_data(all *all_data);
void check_partier(all *all_data);


int main(void){
    int i, data_in_file;
    all *all_data;
    stemmeseddel *aalborg_2015;
    
    all_data = (all *)calloc(1,sizeof(all));
    aalborg_2015 = (stemmeseddel *)calloc(1,sizeof(stemmeseddel));  
   
    data_in_file = count_file_data();

    all_data->temp_kan = (kandidat *)calloc(data_in_file, sizeof(kandidat));
    
    load_file_data(all_data);

    check_partier(all_data);

    
       
    
    for(i = 0; i < all_data->total_loaded; i++){
        printf("Navn %s\n", all_data->temp_kan[i].navn);
    }   

    return 0;
}

int count_file_data(void){
  int scan_control, file_lines = 1;
  FILE *fp;

  fp = fopen("stemmeseddel.txt", "r");
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

void load_file_data(all *all_data){

    FILE *fp;
    int  i = 0;   

    fp = fopen("stemmeseddel.txt", "r");
     

    if (fp != NULL){
        while(!(feof(fp))){
            fscanf(fp, " %[abcdefghijklmnopqrstuvwxzyABCDEFGHIJKLMNOPQRSTUVWXZY.- ]:", all_data->temp_kan[i].navn);
            i++;
            all_data->total_loaded += 1;      
        }
    }
    fclose(fp);
}

void check_partier(all *all_data){

     int i;

     for(i = 0; i < all_data->total_loaded; i++){
         if(strchr(all_data->temp_kan[i].navn, '.')){
             printf("I found one in string %s\n", all_data->temp_kan[i].navn);
             all_data->total_parties += 1;
             printf("Total parties is now %d\n", all_data->total_parties);
             
         }
     }
}
       

