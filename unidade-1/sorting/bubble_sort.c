// Compara elementos conseuctivos e troca a posição caso seja menor/maior.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// n - 2 - i -> pois a cada iteração, a lista estará ordenada i posições a partir do final.
void bubbleSort(int * A, int n) {
  for (int i = 0; i <= n - 1 ; i++) {
    for (int j = 0; j <= n - 2 - i ; j++) {
      if(A[j+1] < A[j]) {
        int aux = A[j];
        A[j] = A[j+1];
        A[j+1] = aux;
      }
    }
  }
}

int main() {
  int vector[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  bubbleSort(vector, 10);

  for (int i = 0; i < 10; i++) {
    printf("%d ", vector[i]);
  }

  return 0;
}