#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * shift_table(char * P) {
  int i, j, size = 256, m = strlen(P);
  int * table = malloc(size * sizeof(int));
  for (i = 0; i < 256; i++) table[i] = m;
  for (j = 0; j < m - 1; j++) table[P[j]] = m - 1 - j;


  return table;
}

void hoorspool_matching(char * P, char * T, int * indices, int * n_indices) {
  int k, i, m = strlen(P), n = strlen(T);
  int * table = shift_table(P);
  i = m - 1;
  while (i < n) {
    k = 0;
    while (k < m && P[m - 1 - k] == T[i - k]) k++;
    if (k == m) indices[(*n_indices)++] = i - m + 1;
    i += table[T[i]];
  }

}

int main() {
  char P[200];
  char T[200];
  fgets(T, sizeof(P), stdin);
  fgets(P, sizeof(T), stdin);
  int indices[strlen(T) / strlen(P)];
  int n_indices = 0;
  hoorspool_matching(P, T, indices, &n_indices);
  // printf("indices: %d", n_indices);
  if(n_indices == 0) {
    printf("-1");
  } else {
    for(int i = 0; i < n_indices; i++) printf("%d\n", indices[i]);
  }

  return 0;
}