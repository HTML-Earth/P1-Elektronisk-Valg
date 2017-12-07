#include <assert.h>
#include <time.h>
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
void test_generic(int base, char *a, char *b, char *expected, char symbol);
void test_generic_base256(char *a, char *b, char *expected, char symbol);

int main(int argc, char *argv[]){

    if (argc < 2) { /* no arguments */
        automated_test();
        printf("\nALL TESTS COMPLETED\n");
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
    bigint *n1, *n2, *result;
    char nc1[MAX_NUMBER], nc2[MAX_NUMBER];
    int i, func_choice, done = 0;

    while(!done){
        printf("Enter values for two positive numbers, with the largest value first. Enter at least one 0 to exit program:\n");
        scanf(" %s %s", nc1, nc2);

        printf("Entered values are %s and %s\n", nc1, nc2);

        if ((strcmp(nc1, "0") != 0) && (strcmp(nc2, "0") != 0)){

            n1 = create_bigint_from_string(10, nc1);
            n2 = create_bigint_from_string(10, nc2);

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
            for (i = result->length - 1; i >= 0; i--) {
                printf("%d", result->digits[i]);
            }
            printf("\n");
        }
        else done = 1;
    }
}

void automated_test() {
    /*
    bigint *a, *b, *r, *r2;
    a = create_bigint_from_string(256, "5:0:");
    b = create_bigint_from_string(256, "1:0:0:");

    bigint_print(a);
    printf("\n");
    bigint_print(b);
    printf("\n");

    r = bigint_multiply(a, b);

    bigint_print(r);
    printf("\n");

    r2 = bigint_convert_base(r, 10, 0, 0, 10);

    bigint_print(r2);
    printf("\n");
    */

    printf("TESTING bigint_add:\n\n");
    test_add("20105", "16785276", "16805381");
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

    /*
    test_subtract("1000000000000","739870000000","260130000000");
    test_subtract("233716","73987","159729");
    test_subtract("23371600000","7398700000","15972900000");
    */

    printf("TESTING bigint_multiply:\n\n");
    test_multiply("2","5","10");
    test_multiply("25","25","625");
    test_multiply("999999","0","0");
    test_multiply("10000","10","100000");
    test_multiply("1000000","10","10000000");

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
    /*
    test_modulus("1000000000000", "73987", "68531");
    test_modulus("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "73987", "23194");
    */

    printf("TESTING bigint_pow:\n\n");
    test_pow("10","2","100");
    test_pow("10","3","1000");
    /*
    test_pow("10","10","10000000000");
    test_pow("10", "100", "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    test_pow("9", "100", "265613988875874769338781322035779626829233452653394495974574961739092490901302182994384699044001");
    test_pow("10", "383", "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    test_pow("9", "1000", "1747871251722651609659974619164660570529062487435188517811888011810686266227275489291486469864681111075608950696145276588771368435875508647514414202093638481872912380089977179381529628478320523519319142681504424059410890214500500647813935818925701905402605484098137956979368551025825239411318643997916523677044769662628646406540335627975329619264245079750470862462474091105444437355302146151475348090755330153269067933091699479889089824650841795567478606396975664557143737657027080403239977757865296846740093712377915770536094223688049108023244139183027962484411078464439516845227961935221269814753416782576455507316073751985374046064592546796043150737808314501684679758056905948759246368644416151863138085276603595816410945157599742077617618911601185155602080771746785959359879490191933389965271275403127925432247963269675912646103156343954375442792688936047041533537523137941310690833949767764290081333900380310406154723157882112449991673819054110440001");
    test_pow("23194","767","1750353299879157785232641973854551325138491279314413705600403328362476672300252218256856124666923244243036420478412856651654079368934905361762964701285588956497791551423951385862725047441525302309036097606775310328478344118566524791664318114621586587225353187276270184435525009626452832271157843344296938755963143830221402623167698957402506762504695391155944646269652352603757478428150920176214750295661077179764022175340777369186283925148025985213411504861344327768391840569284166564572488537216594562736737005715442782530761438911203735797669257997442814545726345304751708042923549260614258442399467889576898964180356729005265396987666261317257928955423428622176512617112248683698535638643866691259182304603779082062615517085300805543053024191104556771566642062852583899633349932679021280357964901769893541386174268346898598242267663444471981207093120550163588771719561764154828969666298149700622477346032274450080979403929075722369339347370335718464609412203637549298170829323027622083191058397036900314356105131752815386286397286163941029940042845377966169490917433064239822873695183954539029576425423690768964284460144260679495328087454027922660590184970946131169776836024270681472186374835616346475484579954000394734493470543199033242363318974977709984508509729471074853695791569709251867612654191186232652072852992183568048501039011738562231215589570998678591056741744021955770495654999495325001563469638891175697340440213843357648161073514106634453603667513925033689356624494150599572495993050963202527082482652526562960620810608758304957381789916494243725213920977129388341132139054223713941257603921968483274072863474423001734486037929064546651519248000942425877072487644747999852903523295813551278067031541560940537288774708516192770701171711506291897250968300696128075096046982297624615491881348486577324616327685718408387733124952144295005451377796407958621188013829015312776385598814182028447652606832028609591120539030905026855756171194808488415225674412078759954076448253147838176081686451352467835401684265391490198588995257080200034330429238229665520459326705216753527295481724808554602079413798144454189753084925144363807175389281420624217719149087940816407058302194945803009216080012946165845651138729113767843416863547392224329456329258364554569195928697488394265029552267238463836846001840315267281626666192412708443872874388596971706438697385574025862319634013828546117654693174783870333420392107719775035697562894166217048015933743815029163408831331842882611689876428539340174919170547415360247473364564910205704278309039047312225358824980660952344556898404797390781651011683000775706549132829036533095579867144339731062657232899048381734115084546804119420579720561658505046856204001327507233725628522689495723302306046103930108875504990008572890825497931265038200970793902601948509656299772134177799536056517295865164569506778514742036364225287777398662752965182579822352281563395610171121720098120934494927073764620463775261046525657765944775375241974213325155126819845332613997663066907960171798003641531521648758319766968180256534895155337821184012254036572925980187927098520748094715013228494016574354374019792819270158023052543284380623489885515319898618255445468155351833834951663261144767908067512155466991705762104379462527507785097137838607638107059932611569780456650445633603281173159789980327918077300423119601664");
    */
}

void test_add(char *a, char *b, char *expected) {
    test_generic_base256(a,b,expected,'+');
}

void test_subtract(char *a, char *b, char *expected) {
    test_generic_base256(a,b,expected,'-');
}

void test_multiply(char *a, char *b, char *expected) {
    test_generic_base256(a,b,expected,'*');
}

void test_divide(char *a, char *b, char *expected) {
    test_generic_base256(a,b,expected,'/');
}

void test_modulus(char *a, char *b, char *expected) {
    test_generic_base256(a,b,expected,'%');
}

void test_pow(char *a, char *b, char *expected) {
    test_generic_base256(a,b,expected,'p');
}

void test_compare(char *a, char *b, int expected) {
    bigint *bi_a, *bi_b;
    int actual;
    char c_expected, c_actual;

    switch (expected) {
        case -1: c_expected = '<'; break;
        case 0: c_expected = '='; break;
        case 1: c_expected = '>'; break;
    }

    printf("Expected: %s %c %s\n", a, c_expected, b);

    bi_a = create_bigint_from_string(10, a);
    bi_b = create_bigint_from_string(10, b);

    actual = bigint_compare(bi_a, bi_b);

    bigint_clear(&bi_a);
    bigint_clear(&bi_b);

    switch (actual) {
        case -1: c_actual = '<'; break;
        case 0: c_actual = '='; break;
        case 1: c_actual = '>'; break;
    }

    printf("     Got: %s %c %s\n\n", a, c_actual, b);
    assert(expected == actual);
}

void test_generic(int base, char *a, char *b, char *expected, char symbol) {
    bigint *bi_a, *bi_b, *bi_actual;
    char str_actual[MAX_DIGITS];
    clock_t start_t, end_t;
    double total_t;

    printf("    %s\n  %c %s\n  = %s\n", a, symbol, b, expected);

    bi_a = create_bigint_from_string(base, a);
    bi_b = create_bigint_from_string(base, b);

    start_t = clock();

    switch (symbol){
        case '+' : bi_actual = bigint_add(bi_a, bi_b);      break;
        case '-' : bi_actual = bigint_subtract(bi_a, bi_b); break;
        case '*' : bi_actual = bigint_multiply(bi_a, bi_b); break;
        case '/' : bi_actual = bigint_divide(bi_a, bi_b);   break;
        case 'p' : bi_actual = bigint_pow(bi_a, bi_b);      break;
        case '%' : bi_actual = bigint_modulus(bi_a, bi_b);  break;
        default : printf("Invalid symbol\n");
    }

    end_t = clock();
    total_t = (double)(end_t - start_t) / (double)CLOCKS_PER_SEC;

    bigint_print_string(str_actual, bi_actual);

    bigint_clear(&bi_actual);

    bigint_clear(&bi_a);
    bigint_clear(&bi_b);

    printf("Got %s\n", str_actual);
    printf("Calculation took: %5.4f seconds (%d clocks)\n\n", total_t, end_t - start_t);
    assert((strcmp(expected, str_actual)) == 0);
}

void test_generic_base256(char *a, char *b, char *expected, char symbol) {
    bigint *bi_a, *bi_b, *bi_a_256, *bi_b_256, *bi_expected, *bi_expected_256;
    char str_a[MAX_DIGITS], str_b[MAX_DIGITS], str_expected[MAX_DIGITS];

    printf("Converting");
    bi_a = create_bigint_from_string(10, a); printf(".");
    bi_b = create_bigint_from_string(10, b); printf(".");
    bi_expected = create_bigint_from_string(10, expected); printf(".");

    bi_a_256 = bigint_convert_base(bi_a, 256, 2, 5, 6);
    bigint_clear(&bi_a); printf(".");
    bi_b_256 = bigint_convert_base(bi_b, 256, 2, 5, 6);
    bigint_clear(&bi_b); printf(".");
    bi_expected_256 = bigint_convert_base(bi_expected, 256, 2, 5, 6);
    bigint_clear(&bi_expected); printf(".");

    bigint_print_string(str_a, bi_a_256);
    bigint_clear(&bi_a_256); printf(".");
    bigint_print_string(str_b, bi_b_256);
    bigint_clear(&bi_b_256); printf(".");
    bigint_print_string(str_expected, bi_expected_256);
    bigint_clear(&bi_expected_256); printf(".");
    printf("DONE\n");

    test_generic(256, str_a, str_b, str_expected, symbol);
}
