#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// gcc corte_de_hastes.c -o ./output/corte_de_hastes
// ./output/corte_de_hastes.exe < ./inputs/corte_de_hastes.txt

void print_haste(int * valores_por_corte, int tamanho_haste) {
  for (int i = 1; i <= tamanho_haste; i++) {
    printf("Comprimento %d | Valor: %d\n", i, valores_por_corte[i]);
  }
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

int table[10000];

void inicializar_tabela(int n) {
  int i;
  table[0] = 0;
  for(i = 1; i <= n; i++) {
    // printf("Preenchendo %d\n", i);
    table[i] = INT_MIN;
  }
}

int corte_de_hastes(int * valores_por_corte, int tamanho_haste) {
  int i;

  if (table[tamanho_haste] >= 0) return table[tamanho_haste];

  int corte = INT_MIN;
  for(i = 1; i <= tamanho_haste; i++) {
    corte = max(corte, valores_por_corte[i] + corte_de_hastes(valores_por_corte, tamanho_haste - i));
  }
  // printf("TABLE: %d = %d\n", tamanho_haste, corte);
  table[tamanho_haste] = corte;
  return table[tamanho_haste];
}

int main() {
  int tamanho_haste, n, indice_valores = 0;
  scanf("%d", &tamanho_haste);
  inicializar_tabela(tamanho_haste);

  int valores_por_corte[tamanho_haste + 1];
  valores_por_corte[indice_valores++] = 0;

  while (1) {
    scanf("%d", &n);
    if (n == 0) break;

    valores_por_corte[indice_valores++] = n;
  }

  int valor_maximo = corte_de_hastes(valores_por_corte, tamanho_haste);

  // print_haste(valores_por_corte, tamanho_haste);
  printf("%d", valor_maximo);

  return 0;
}