#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char obter_sinal(int coeficiente) {
  return coeficiente >= 0 ? '+' : '-';
}

void derivada(int * coeficiente, int * expoente) {
  *coeficiente *= *expoente;
  *expoente -= 1;
}

int main() {
  char formatado[20];
  int times = 0;
  scanf("%d", &times);

  int coeficiente, expoente;
  char variavel;
  
  while (times != 0) {
    int derivacoes = 0;
    for (int i = 0; i < times; i++) {
      scanf("%d %c %d", &coeficiente, &variavel, &expoente);

      if (!i) printf("f'(%c)=", variavel);
      if (!expoente || !coeficiente) continue;

      derivada(&coeficiente, &expoente);
      derivacoes++;

      !expoente ? 
        printf("%c%d", obter_sinal(coeficiente), abs(coeficiente)) 
          : 
        printf("%c%d%c^%d", obter_sinal(coeficiente), abs(coeficiente), variavel, expoente);
    }

    derivacoes == 0 ? printf("0\n"): printf("\n");
    scanf("%d", &times);
  }

  return 0;
}