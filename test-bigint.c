#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "bigints.h"

#define MAX_NUMBER 10

void automated_test();
void test_function(char *a, char *b, char *expected, char symbol);
void test_add(char *a, char *b, char *expected);
void test_subtract(char *a, char *b, char *expected);
void test_multiply(char *a, char *b, char *expected);
void test_divide(char *a, char *b, char *expected);
void test_modulus(char *a, char *b, char *expected);
void test_pow(char *a, char *b, char *expected);
void test_compare(char *a, char *b, char *expected);

int main(void){
    /*
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
    */

    automated_test();

    return 0;
}

void automated_test() {
    printf("TESTING bigint_add:\n\n");
    test_add("1","1","2");
    test_add("2","2","4");
    test_add("1","9","10");
    test_add("1","99","100");
    test_add("1","999","1000");
    test_add("123","877","1000");

    printf("TESTING bigint_subtract:\n\n");
    test_subtract("2","1","1");
    test_subtract("10000000","1","9999999");
    test_subtract("123456789","123456789","0");

    printf("TESTING bigint_multiply:\n\n");
    test_multiply("2","5","10");
    test_multiply("25","25","625");
    test_multiply("999999","0","0");

    printf("TESTING bigint_divide:\n\n");
    test_divide("10","2","5");
    test_divide("81","9","9");
    test_divide("1000","100","10");

    printf("TESTING bigint_modulus:\n\n");
    test_modulus("0","15","0");
    test_modulus("15","5","0");
    test_modulus("15","20","15");

    printf("TESTING bigint_pow:\n\n");
    test_pow("10","10","10000000000");
}

void test_function(char *a, char *b, char *expected, char symbol) {
    bigint bi_a, bi_b, bi_actual;
    char str_actual[MAX_DIGITS];

    printf("    %s\n  %c %s\n  = %s\n", a, symbol, b, expected);

    bi_a = create_bigint_from_string(a);
    bi_b = create_bigint_from_string(b);

    switch (symbol){
        case '+' : bi_actual = bigint_add(bi_a, bi_b);      break;
        case '-' : bi_actual = bigint_subtract(bi_a, bi_b); break;
        case '*' : bi_actual = bigint_multiply(bi_a, bi_b); break;
        case '/' : bi_actual = bigint_divide(bi_a, bi_b);   break;
        case 'p' : bi_actual = bigint_pow(bi_a, bi_b);      break;
        case '%' : bi_actual = bigint_modulus(bi_a, bi_b);  break;
        default : printf("Invalid symbol\n");
    }

    bigint_print_string(str_actual, bi_actual);

    printf("Got %s\n\n", str_actual);
    assert((strcmp(expected, str_actual)) == 0);
}

void test_add(char *a, char *b, char *expected) {
    test_function(a,b,expected,'+');
}

void test_subtract(char *a, char *b, char *expected) {
    test_function(a,b,expected,'-');
}

void test_multiply(char *a, char *b, char *expected) {
    test_function(a,b,expected,'*');
}

void test_divide(char *a, char *b, char *expected) {
    test_function(a,b,expected,'/');
}

void test_modulus(char *a, char *b, char *expected) {
    test_function(a,b,expected,'%');
}

void test_pow(char *a, char *b, char *expected) {
    test_function(a,b,expected,'p');
}

void test_compare(char *a, char *b, char *expected) {

}
