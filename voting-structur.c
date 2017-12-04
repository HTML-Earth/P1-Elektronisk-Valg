#include <stdlib.h>
#include <stdio.h>

#define MAX_CHARS 50

struct stemmeseddel{
    struct partier *p_2015;
    struct kanditat *k_2015;
};

struct partier{
    char p_navn[MAX_CHARS];
    int stemme_cnt;
};

struct kanditat{
    char k_navn[MAX_CHARS];
    int stemme_cnt;
};

struct valgkreds{
    char v_navn[MAX_CHARS];
    int ant_partier;
    int ant_kandidater;
    struct stemmeseddel;
};

typedef struct valgkreds valgkreds;
typedef struct stemmesdl stemmeseddel;
typedef struct partier partier;
typedef struct kanditat kandidat;

void check_vote_info(valgkreds *info_2015);

int main(void){

    valgkreds *info_2015;
  
    info_2015 = (valgkreds*)calloc(1, sizeof(valgkreds));

    check_vote_info(info_2015);
    

    return 0;
}

void check_vote_info(valgkreds *info_2015){

    FILE *fp;
    int scan_control, file_lines = 0;
    

    fp = fopen("Liste_af_Kandidater.txt", "r");

    if (fp != NULL){
        while((scan_control = fgetc(fp))  != 33){
            if((scan_control = fgetc(fp)) != 33){      
                if (scan_control == '\n'){
                    file_lines++;
                }
            }
        }
    }
    printf("This many lines were counted: %d\n", file_lines); 
  fclose(fp);
}
