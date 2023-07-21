// Seleciona o menor/maior elemento da lista e coloca no início da lista.
// A cada iteração, a lista estará ordenada i posições a partir do início.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void selectionSort(int * A, int n) {
  int min;
  for (int i = 0; i <= n - 2; i++) {
    min = i;
    for (int j = i + 1; j <= n - 1; j++) {
      if (A[j] < A[min]) min = j;
    }
    
    int aux = A[min];
    A[min] = A[i];
    A[i] = aux;
  }
}

int main() {
  int vector[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  selectionSort(vector, 10);

  for (int i = 0; i < 10; i++) {
    printf("%d ", vector[i]);
  }

  return 0;
}