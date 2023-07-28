#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int * Crivo(int n) {
  int * A = (int*)malloc((n + 1) * sizeof(int));

  for (int p = 2; p <= n; p++) {
    A[p] = p;
  }
  for (int p = 2; p * p <= n; p++) {
    if (A[p] != 0) {
      int j = p * p;
      while (j <= n) {
        A[j] = 0;
        j += p;
      }
    }
  }

  int t = 0;
  for (int i = 2; i < n; i++) {
    if (A[i] != 0) {
      t++;
    }
  }

  int * L = (int*)malloc(t * sizeof(int));

  int i = 0;
  for (int p = 2; p <= n; p++) {
    if (A[p] != 0) {
      L[i] = A[p];
      i++;
    }
  }

  for (int i = 0; i < t; i++) {
    printf("| %d |", L[i]);
  }

  free(A);

  return L;
}

int main() {
  int n = 36;
  int * result = Crivo(n);
  free(result);
  return 0;
}