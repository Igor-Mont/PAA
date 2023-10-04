#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * shift_table(char * P) {
  int i, j, size = 256, m = strlen(P);
  int * table = malloc(size * sizeof(int));
  for (i = 0; i < size; i++) table[i] = m;
  for (j = 0; j < m - 1; j++) table[P[j]] = m - 1 - j;

  return table;
}

int hoorspool_matching(char * P, char * T) {
  long k, i, m = strlen(P), n = strlen(T);
  int * table = shift_table(P);
  i = m - 1;
  while (i < n) {
    k = 0;
    while (k < m && (P[m - 1 - k] == T[i - k] || P[m - 1 - k] == '_')) k++;
    if (k == m) return (long)(i - m + 1);
    i += table[T[i]];
  }

  return -1;
}

int main() {
  long sizeP, sizeT;
  // scanf("%d %d", &sizeT, &sizeP);
    if (scanf("%ld %ld", &sizeT, &sizeP) != 2) {
    printf("Erro na leitura dos tamanhos.\n");
    return 1;
  }

  char T[sizeT + 1];
  char P[sizeP + 1];

  if (scanf("%s", T) != 1 || scanf("%s", P) != 1) {
    printf("Erro na leitura das strings.\n");
    return 1;
  }
  // scanf("%s", T);
  // scanf("%s", P);
  
  long index = hoorspool_matching(P, T);
  if(index == -1) {
    printf("Nao descendente");
  } else {
    printf("%d\n", index);
  }

  return 0;
}