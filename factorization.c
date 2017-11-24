#include <stdio.h>

void funktion_factorization(void);

int main(void){

funktion_factorization();

return 0;

}
void funktion_factorization(void){

  int d = 0, e = 0, k = 0, fi = 0;

  printf("find d and k from two values e and fi \n" );

  scanf("%d %d", &e, &fi );

  while((d * e) - (k * fi) != 1){

  while ((d * e) < k * fi){
    d++;
  }
  if ((d * e) - k * fi != 1)

  k++;
  }
printf("d e k fi appear as follow:\n" );
printf("1 = %d * %d * (-%d * %d)\n",d, e, k, fi);
printf("d: %d k:  %d\n", d, k);
}
