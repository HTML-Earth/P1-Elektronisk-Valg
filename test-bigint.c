#include <stdio.h>
#include <string.h>
#include "bigints.h"

#define MAX_NUMBER 5

int main(void){

    bigint n1, n2, result;
    char nc1[MAX_NUMBER], nc2[MAX_NUMBER];
    int i, func_choice, done = 0;
    
    while(!done){
        printf("Enter values for two positive numbers, with the largest value first. Enter at least one 0 to exit program:\n");
        scanf(" %s %s", nc1, nc2);
       
        printf("Entered values are %s and %s\n", nc1, nc2);

        if ((strcmp(nc1, "0") != 0) && (strcmp(nc2, "0") != 0)){  
   
            n1 = create_bigint_from_string(nc1); 
            n2 = create_bigint_from_string(nc2);
 
            printf("Now choose between:\n1: Addition\n2: Subtraction\n3: Multiply\n4: Divide\n5: Power\n6: Modulus\n");
            scanf(" %d", &func_choice);

            switch (func_choice){
                case 1 : result = bigint_add(n1, n2);      break;
                case 2 : result = bigint_subtract(n1, n2); break;
                case 3 : result = bigint_multiply(n1, n2); break; 
                case 4 : result = bigint_divide(n1, n2);   break;
                case 5 : result = bigint_pow(n1, n2);      break;
                case 6 : result = bigint_modulus(n1, n2);  break;
                default : printf("You have chosen invalid option\n");
            }
            printf("The result is:");
            for (i = result.length - 1; i >= 0; i--) {
                printf("%d", result.digits[i]); 
            }  
            printf("\n");
        }
        else done = 1;
    }

    return 0;
}
