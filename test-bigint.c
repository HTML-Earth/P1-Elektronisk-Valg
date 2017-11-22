#include <stdio.h>
#include "bigints.h"


int main(void){

    bigint n1, n2, result;
    int i;

    n2 = create_bigint_from_string("10");
    n1 = create_bigint_from_string("10"); 
    


    result = bigint_pow(n2, n1);

    for (i = result.length - 1; i >= 0; i--) {
            printf("%d", result.digits[i]); 
        };


    return 0;
}
