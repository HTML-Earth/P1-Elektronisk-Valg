#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "bigints.h"

#define MAX_NUMBER 10

void manual_test();
void automated_test();
void test_add(char *a, char *b, char *expected);
void test_subtract(char *a, char *b, char *expected);
void test_multiply(char *a, char *b, char *expected);
void test_divide(char *a, char *b, char *expected);
void test_modulus(char *a, char *b, char *expected);
void test_pow(char *a, char *b, char *expected);
void test_compare(char *a, char *b, int expected);
void test_generic(char *a, char *b, char *expected, char symbol);

int main(int argc, char *argv[]){

    if (argc < 2) { /* no arguments */
        automated_test();
    }
    else if (strcmp(argv[1], "manual") == 0) {
        manual_test();
    }
    else {
        printf("Invalid parameters.\n");
        printf("Use 'manual' for manual test.\n");
    }
    return 0;
}

void manual_test()
{
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
}

void automated_test() {
    printf("TESTING bigint_add:\n\n");
    test_add("123", "123", "246");
    test_add("1","1","2");
    test_add("2","2","4");
    test_add("1","9","10");
    test_add("1","10","11");
    test_add("1","11","12");
    test_add("200","300","500");
    test_add("123","877","1000");
    test_add("12","877","889");
    test_add("5","95","100");
    test_add("1","99","100");
    test_add("1","999","1000");
    test_add("2","9999","10001");

    test_add("25", "100", "125");
    test_add("125", "100", "225");
    test_add("225", "400", "625");

    printf("TESTING bigint_subtract:\n\n");
    test_subtract("2","1","1");
    test_subtract("10000000","1","9999999");
    test_subtract("123456789","123456789","0");
    test_subtract("1000000000000","739870000000","260130000000");
    test_subtract("23371600000","7398700000","15972900000");

    printf("TESTING bigint_multiply:\n\n");
    test_multiply("2","5","10");
    test_multiply("25","25","625");
    test_multiply("999999","0","0");

    printf("TESTING bigint_divide:\n\n");
    test_divide("10","2","5");
    test_divide("81","9","9");
    test_divide("1000","100","10");

    printf("TESTING bigint_compare:\n\n");
    test_compare("1","2", -1);
    test_compare("2","1", 1);
    test_compare("2","2", 0);
    test_compare("100000000000001","99", 1);
    test_compare("54321","12345", 1);
    test_compare("260130000000","739870000000", -1);

    printf("TESTING bigint_modulus:\n\n");
    test_modulus("0","15","0");
    test_modulus("15","5","0");
    test_modulus("15","20","15");
    test_modulus("1000000000000", "73987", "68531");
    test_modulus("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "73987", "23194");

    printf("TESTING bigint_pow:\n\n");
    test_pow("10","10","10000000000");
    test_pow("10", "100", "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    test_pow("9", "100", "265613988875874769338781322035779626829233452653394495974574961739092490901302182994384699044001");
    test_pow("10", "383", "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    test_pow("9", "1000", "1747871251722651609659974619164660570529062487435188517811888011810686266227275489291486469864681111075608950696145276588771368435875508647514414202093638481872912380089977179381529628478320523519319142681504424059410890214500500647813935818925701905402605484098137956979368551025825239411318643997916523677044769662628646406540335627975329619264245079750470862462474091105444437355302146151475348090755330153269067933091699479889089824650841795567478606396975664557143737657027080403239977757865296846740093712377915770536094223688049108023244139183027962484411078464439516845227961935221269814753416782576455507316073751985374046064592546796043150737808314501684679758056905948759246368644416151863138085276603595816410945157599742077617618911601185155602080771746785959359879490191933389965271275403127925432247963269675912646103156343954375442792688936047041533537523137941310690833949767764290081333900380310406154723157882112449991673819054110440001");
}

void test_add(char *a, char *b, char *expected) {
    test_generic(a,b,expected,'+');
}

void test_subtract(char *a, char *b, char *expected) {
    test_generic(a,b,expected,'-');
}

void test_multiply(char *a, char *b, char *expected) {
    test_generic(a,b,expected,'*');
}

void test_divide(char *a, char *b, char *expected) {
    test_generic(a,b,expected,'/');
}

void test_modulus(char *a, char *b, char *expected) {
    test_generic(a,b,expected,'%');
}

void test_pow(char *a, char *b, char *expected) {
    test_generic(a,b,expected,'p');
}

void test_compare(char *a, char *b, int expected) {
    bigint bi_a, bi_b;
    int actual;
    char c_expected, c_actual;

    switch (expected) {
        case -1: c_expected = '<'; break;
        case 0: c_expected = '='; break;
        case 1: c_expected = '>'; break;
    }

    printf("Expected: %s %c %s\n", a, c_expected, b);

    bi_a = create_bigint_from_string(a);
    bi_b = create_bigint_from_string(b);

    actual = bigint_compare(bi_a, bi_b);

    free(bi_a.digits);
    free(bi_b.digits);

    switch (actual) {
        case -1: c_actual = '<'; break;
        case 0: c_actual = '='; break;
        case 1: c_actual = '>'; break;
    }

    printf("     Got: %s %c %s\n\n", a, c_actual, b);
    assert(expected == actual);
}

void test_generic(char *a, char *b, char *expected, char symbol) {
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

    free(bi_a.digits);
    free(bi_b.digits);

    bigint_print_string(str_actual, bi_actual);

    free(bi_actual.digits);

    printf("Got %s\n\n", str_actual);
    assert((strcmp(expected, str_actual)) == 0);
}
