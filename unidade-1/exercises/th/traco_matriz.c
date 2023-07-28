#include <stdio.h>
#include <stdlib.h>

int main() {
  int ordem;
  scanf("%d", &ordem);

  float ** matriz = (float **)malloc(ordem * sizeof(float *));
  float * diagonal = (float *)malloc(ordem * sizeof(float));

  for (int i = 0; i < ordem; i++) {
    matriz[i] = (float *)malloc(ordem * sizeof(float));
    for (int j = 0; j < ordem; j++) {
      scanf("%f", &matriz[i][j]);
    }
    diagonal[i] = matriz[i][i];
  }

  float traco = 0;
  printf("tr(A) = ");
  for (int i = 0; i < ordem; i++) {
    traco += diagonal[i];
    if(i + 1 == ordem) {
      printf("(%.2f) = ", diagonal[i]);
      continue;
    }
    printf("(%.2f) + ", diagonal[i]);
  }

  printf("%.2f", traco);

  return 0;
}