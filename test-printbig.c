#include <stdio.h>
#include "bigints.h"
#include <string.h>

#define MAX_CHAR 10000

void bigint_print_to_string(char *str);

int main(void){
    /*char *c1 = "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"*/
    bigint b1;
    char c1[MAX_CHAR];

   
    bigint_print_to_string(c1);

    printf(" I have created string \n");
    
    b1 = create_bigint_from_string(c1);

    printf(" I have created bigint\n");
  
    bigint_print(b1);

    printf(" I have printed bigint\n");

    free(b1.digit); 

    return 0;

}


void bigint_print_to_string(char *str){
    int i, j = 0;
    for (i = 0; i < MAX_CHAR; i++) {
        sprintf(str+j, "1");
        j++;
    }
}
