#include    "encryption.h"
#include    "voting-functions.h"

int main(void){

bigint *code;
int i_code;


printf("Enter code to be encrypted\n");
scanf(" %d", &i_code);

code = encryption(i_code);

bigint_print(code);

code = decryption(code);

printf("\n");

bigint_print(code);

return 0;
}
