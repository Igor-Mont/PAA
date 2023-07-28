#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int calcular_digito(char * chave) {
  int numeros[10];
  int j = 0;
  for (int i = 0; chave[i] != '\0'; i++) {
    if (chave[i] >= '0' && chave[i] <= '9') {
      numeros[j++] = chave[i] - '0';
    }
  }
  int maior = 0;
  int resultado = 0;
  for (int i = 0; i <= 8; i++) {
    if(numeros[i] > maior) {
      maior = numeros[i];
    }

    if ((i + 1) % 3 == 0) {
      resultado += maior;
      maior = 0;
    }
  }
  return resultado % 10 == numeros[9];
}

int main() {
  char chave[14];
  int valores[100];
  int tam = 0;
  
  while(1) {
    scanf("%14s", chave); // evitar buffer overflow
    if(!strcmp(chave, "FIM")) break;
    printf(calcular_digito(chave) ? "VALIDO\n" : "INVALIDO\n");
  }

  return 0;
}